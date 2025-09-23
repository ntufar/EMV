# EMV Terminal Application Architecture

## 1. Introduction

This document provides a high-level overview of the architectural design of the EMV terminal application. The application is a C++ project designed to handle EMV transactions, from card insertion to transaction completion. The architecture is modular and component-based, allowing for flexibility and extensibility.

## 2. Core Architectural Principles

*   **Modularity**: The application is divided into distinct modules, each responsible for a specific phase of the EMV transaction. This promotes separation of concerns and makes the codebase easier to understand and maintain.
*   **Component-Based**: The architecture relies on a component-based model, where services are loaded dynamically based on the application's configuration. This allows for different EMV applications and hardware to be supported by providing the appropriate service implementations.
*   **Data-Centric**: A central `EMV_Context` class is used to store and manage all transaction-related data. This provides a single source of truth for the transaction state and facilitates communication between the different modules.

## 3. High-Level Architecture

The application's architecture can be broadly divided into three layers:

1.  **Application Layer**: This layer contains the main application logic, including the entry point (`emv.cpp`) and the orchestration of the EMV transaction flow.
2.  **Service Layer**: This layer provides the core EMV functionality through a set of services. These services are accessed through the `AccessManager` and include Application Selection, Cryptography, and UI Control.
3.  **Runtime Layer**: This layer provides the underlying runtime environment for the application, including access to system resources, hardware abstraction, and inter-process communication.

## 4. Key Components

### 4.1. AccessManager

The `AccessManager` is the central component of the service layer. It is responsible for:

*   Finding and loading the correct service implementation based on the Application ID (AID).
*   Managing the lifecycle of services.
*   Providing a unified interface for accessing services.

This component-based approach allows for different EMV applications to be supported by providing the appropriate service implementations. For example, a new card reader can be supported by implementing the `SCRControl` service interface and registering it with the `AccessManager`.

### 4.2. ServiceControl

The `ServiceControl` class is the base class for all services. It defines a common interface for services, allowing the `AccessManager` to treat them uniformly. Each service is responsible for a specific aspect of the EMV transaction, such as:

*   **`ApplSelControl`**: Application Selection
*   **`CryptoControl`**: Cryptographic operations
*   **`UIControl`**: User interface control
*   **`SCRControl`**: Smart card reader control

### 4.3. EMV_Context

The `EMV_Context` class is a central data repository for all transaction-related data. It is a base class for all the EMV transaction phase classes, and it provides a mechanism for sharing data between them. The context stores information such as:

*   Transaction amount
*   Transaction type
*   Cardholder verification results
*   Offline data authentication results

### 4.4. EMV Transaction Flow

The EMV transaction flow is implemented as a series of distinct phases, each encapsulated in its own class. These classes inherit from `EMV_Context` and have access to the shared transaction data. The main phases are:

1.  **`ApplicationInitialization`**: Handles the "Initiate Application Processing" phase, including reading the application data from the card.
2.  **`OfflineDataAuthentication`**: Performs Static Data Authentication (SDA) or Dynamic Data Authentication (DDA) to authenticate the card.
3.  **`ProcessingRestrictions`**: Checks the application usage control and version numbers.
4.  **`CardholderVerification`**: Performs cardholder verification (e.g., PIN entry).
5.  **`TerminalRiskManagement`**: Performs terminal risk management to check for exceptions.
6.  **`TerminalActionAnalysis`**: Determines the terminal's action (approve, decline, or go online) based on the results of the previous phases.
7.  **`CardActionAnalysis`**: Analyzes the card's response to the `GENERATE AC` command.
8.  **`OnLineProcessing`**: Handles online transaction processing, if required.
9.  **`IssuerScriptProcessing`**: Processes any scripts sent by the issuer.
10. **`Completion`**: Completes the transaction and provides the final outcome.

---

## 5. Detailed Layer View

### 5.1 Application Layer (entry and orchestration)
- Entry point: `emv.cpp` coordinates the transaction lifecycle and orchestrates the sequence of phases.
- Responsibilities:
  - Initialize runtime and register services with `AccessManager`.
  - Build the `EMV_Context` with terminal parameters and transaction inputs (amount, type, currency).
  - Invoke each phase in order and handle branching decisions (e.g., online required).
  - Collect and return the final transaction result.

### 5.2 Service Layer (capabilities behind interfaces)
- Common base: `ServiceControl` and an `AccessManager`-style locator.
- Core interfaces:
  - `ApplSelControl`: Discover AIDs (PSE/PPSE), select application, read AFL/ADF.
  - `SCRControl`: Card I/O (connect, transmit APDUs, power on/off, status).
  - `UIControl`: Display messages and capture inputs (PIN, confirmation).
  - `CryptoControl`: RSA/SHA, key recovery/verification, ARQC/TC/ARPC support.
- Implementations can be swapped per AID, scheme, or device family.

### 5.3 Runtime Layer (adapters and integration)
- Bridges OS/hardware to service interfaces.
- May include device drivers, IPC clients, timers, KMS integration, and logging sinks.
- Located under `Runtime/` and other platform folders.

---

## 6. Data Model and Objects

### 6.1 EMV_Context
Holds canonical transaction state, including but not limited to:
- Selected AID and application version
- Terminal capabilities and risk parameters
- Amount, other amounts, currency, transaction type
- Track 2 data, PAN, PAN sequence number
- AFL, AIP, CDOL1/CDOL2
- Offline authentication results (SDA/DDA/CDA)
- CVM results (e.g., plaintext/enciphered PIN verified, signature required)
- Terminal action decision inputs and outputs
- Cryptograms (ARQC/TC/AAC), ATC, UN, IAD
- Online response and issuer scripts

### 6.2 Command and Data Encodings
- APDUs: `C_APDU`, `R_APDU`, and `APDU` helpers in `Utility/` manage command building and parsing.
- TLV: `tlv_parser.*`, `tlv_creator.*`, and `DataObject.*` encode/decode EMV TLV structures.
- DOL: `dol_parser.*` composes CDOLs for `GENERATE AC` and other commands.

---

## 7. Transaction Phases (Responsibilities, Inputs, Outputs)

For each phase, the pattern is: read required fields from `EMV_Context`, perform operations, update context with results, and return status.

1. `ApplicationInitialization`
   - Inputs: terminal params, candidate AIDs, PSE/PPSE, ATR
   - Ops: Select application, read AIP/AFL, read records
   - Outputs: AID, AIP, AFL, application data (PAN, dates, usage control)

2. `OfflineDataAuthentication`
   - Inputs: SDA/DDA indicators, ICC/Issuer/CA keys, signed static data
   - Ops: Verify signatures (SDA), perform DDA or CDA as configured
   - Outputs: ODA result flags, recovered data, ICC public key (if recovered)

3. `ProcessingRestrictions`
   - Inputs: application effective/expiry dates, version, usage control
   - Ops: Validate dates, version compatibility, AUC checks
   - Outputs: Acceptance flags or restriction failure indicators

4. `CardholderVerification`
   - Inputs: CVM list and rules, terminal capabilities, CVM results
   - Ops: Select and execute CVM (e.g., online PIN, enciphered/plaintext PIN)
   - Outputs: CVM performed and result code

5. `TerminalRiskManagement`
   - Inputs: floor limit, random selection params, exception file, velocity data
   - Ops: Floor limit check, random selection, exception/velocity checks
   - Outputs: Risk flags influencing TAA decision

6. `TerminalActionAnalysis`
   - Inputs: TACs, IACs, risk flags, ODA and CVM results
   - Ops: Determine requested cryptogram type (ARQC/TC/AAC)
   - Outputs: Terminal decision and CDOL1 for `GENERATE AC`

7. `CardActionAnalysis`
   - Inputs: CDOL1, UN, ATC, IAD, terminal decision
   - Ops: Send `GENERATE AC`, parse response
   - Outputs: ARQC/TC/AAC, ATC, IAD; possibly triggers online

8. `OnLineProcessing`
   - Inputs: ARQC and transaction data
   - Ops: Build ISO 8583 (or host protocol), send to issuer/acquirer, validate ARPC
   - Outputs: Host response, ARPC validation result, scripts

9. `IssuerScriptProcessing`
   - Inputs: Issuer scripts (71/72), card state
   - Ops: Transmit scripts to card and record results
   - Outputs: Script execution status

10. `Completion`
    - Inputs: All prior results and host decision
    - Ops: Finalize outcome, print/return receipt data, update logs
    - Outputs: Transaction result (approved/declined), audit trail

---

## 8. Control Flow (Textual Sequence)

1. Terminal powered and services registered
2. Card inserted/presented; ATR received
3. Application selection (PSE/PPSE or AID list) → AID chosen
4. Read application data (AIP/AFL) and records
5. Offline data authentication (SDA/DDA/CDA)
6. Processing restrictions checks
7. Cardholder verification (per CVM list)
8. Terminal risk management
9. Terminal action analysis → request AC type
10. Card action analysis → `GENERATE AC` response
11. If ARQC → go online, validate response (ARPC), process scripts
12. Completion → produce final outcome and persist artifacts

---

## 9. Extensibility

- Add new hardware: implement `SCRControl` and register with `AccessManager`.
- Customize UI: implement `UIControl` for your display/keypad stack.
- Swap crypto: implement `CryptoControl` using your KMS/HSM or OpenSSL.
- Support new schemes: parameterize per AID via `AccessManager` lookups.

---

## 10. Error Handling and Logging

- Each phase returns status codes and updates context with failure reasons.
- Fail-closed for critical checks (ODA failure, CVM failed when required).
- Structured logging at phase boundaries with redaction of sensitive data.
- Retry policies for transient I/O (reader communication, host connectivity).

---

## 11. Security Considerations

- Protect keys and sensitive data (PAN, PIN, cryptograms); avoid logging secrets.
- Zeroize sensitive buffers after use where feasible.
- Enforce PIN entry via secure PIN pad when required by CVM rules.
- Validate certificate chains and key lifetimes.

---

## 12. Runtime Integration Notes

- Device drivers: map reader events to `SCRControl` connect/disconnect and APDU transport.
- Time and randomness: provide a CSPRNG for UN and cryptographic operations.
- Host communication: implement your ISO 8583 or host protocol adapter in `OnLineProcessing`.
- Persistence: store required audit and reconciliation records per local regulation.

---

## 13. File Map (Reference)

- `EMV_Library/`: core phases (`*Initialization*`, `*Authentication*`, `*Verification*`, `*Management*`, `*Analysis*`, `OnLineProcessing`, `Completion`), context (`EMV_Context.*`, `Context.*`), helpers (`ApplSelector.*`, `scr_command.*`, `Prompter.*`).
- `Utility/`: APDU/TLV/DOL helpers.
- `Runtime/`: adapters and platform services.
- `emv.*`: entry and orchestrator glue.

---

## 14. Future Enhancements

- Add CDA path and certification artifacts, if not already present.
- Introduce unit tests and mocks for service interfaces.
- Provide example implementations for desktop readers and a sample host.
- Add continuous integration with static analysis and sanitizers.

---

## 15. Service Interface Contracts (Indicative)

Below are indicative contracts to guide implementations. Exact signatures depend on headers present in the codebase.

- `SCRControl`
  - Responsibilities: reader lifecycle, APDU transport, status monitoring
  - Key methods (indicative):
    - `bool connect()` / `void disconnect()`
    - `bool isCardPresent() const`
    - `bool transmit(const C_APDU& cmd, R_APDU& resp)`
    - Events: card inserted/removed callbacks or poll model

- `UIControl`
  - Responsibilities: user messaging and input (PIN, selections)
  - Key methods:
    - `void displayMessage(const std::string& msg)`
    - `PinResult requestPinEntry(PinConstraints constraints)`
    - `bool confirm(const std::string& prompt)`

- `CryptoControl`
  - Responsibilities: hashing, RSA verify/recover, ARQC/ARPC support
  - Key methods:
    - `bool verifySda(const ByteArray& signedData, const PublicKey& issuerKey)`
    - `bool performDda(const ByteArray& iccDynData, const PublicKey& iccKey)`
    - `bool computeArpc(const ByteArray& arqc, const ByteArray& authRespCode, ByteArray& arpc)`

- `ApplSelControl`
  - Responsibilities: AID discovery and selection policy
  - Key methods:
    - `std::vector<Aid> listCandidateAids()`
    - `Aid decide(const std::vector<Aid>& candidates, const TerminalPolicy& policy)`

Contracts should avoid leaking platform specifics; use value objects (AID, Key, ByteArray) and error/status enums.

---

## 16. Configuration Schema (Indicative)

Configuration can be provided via file, registry, or code. Suggested keys:

- Terminal
  - `countryCode`, `currencyCode`, `capabilities`, `additionalCapabilities`
  - `floorLimit`, `tacDenial`, `tacOnline`, `tacDefault`
- Risk and Random Selection
  - `targetPercentage`, `maxTargetPercentage`, `threshold`
- AID Profiles
  - `aid`, `appVersion`, `ddaSupported`, `cdaPreferred`, `cvmListOverrides`
- Reader
  - `contact`, `contactless`, `timeoutMs`, `exclusiveMode`
- Host
  - `protocol` (e.g., iso8583), `endpoint`, `keys`

Use strong typing when loading into `EMV_Context` and validate on startup.

---

## 17. Threading and Concurrency

- Model: single-transaction, single-threaded flow for determinism.
- Concurrency points:
  - Reader event handling may be asynchronous; serialize into the transaction loop.
  - Host I/O can be asynchronous; provide a synchronous facade to the phase layer.
- Synchronization: 
  - Ensure `EMV_Context` writes are serialized; avoid concurrent mutation.
  - If background logging is used, queue immutable snapshots.

---

## 18. Performance Characteristics

- Hot paths: APDU round trips (P1/P2 reads, `GENERATE AC`), TLV parsing, RSA.
- Optimizations:
  - Cache parsed TLVs and avoid repeated scans of AFL records.
  - Use zero-copy views for TLV slices where safe.
  - Prefer hardware crypto or accelerated libraries when available.
- Targets:
  - Contact: end-to-end < 2.5s typical; Contactless: < 500ms to first decision.

---

## 19. Error Taxonomy (Indicative)

- Reader/Transport: timeouts, protocol errors, card removed
- Data/Parsing: TLV malformed, AFL out-of-range, tag missing
- Authentication: key not found, signature invalid, expired cert
- CVM: PIN entry failed, unsupported method required
- Risk/Policy: floor limit exceeded, exception file hit
- Host/Network: connect failure, response invalid, ARPC mismatch
- Scripts: execution failed, SW1/SW2 not accepted

Use structured error enums and attach contextual fields (tag, P1/P2, SW) for diagnostics.

---

## 20. Compliance Mapping (EMV Book 3)

- 10.x Initiate Application Processing → `ApplicationInitialization`
- 11.x Read Application Data → `ApplicationInitialization`
- 12.x Data Authentication → `OfflineDataAuthentication` (SDA/DDA/CDA)
- 13.x Processing Restrictions → `ProcessingRestrictions`
- 14.x Cardholder Verification → `CardholderVerification`
- 15.x Terminal Risk Management → `TerminalRiskManagement`
- 16.x Terminal Action Analysis → `TerminalActionAnalysis`
- 17.x Card Action Analysis → `CardActionAnalysis`
- 18.x Online Processing → `OnLineProcessing`
- 19.x Issuer Script Processing → `IssuerScriptProcessing`
- 20.x Completion → `Completion`

---

## 21. Security Threat Model (Abbreviated)

- Assets: PAN, Track 2, PIN, keys, cryptograms, scripts, logs.
- Threats:
  - Eavesdropping on APDU/host links; Mitigation: secure transport, TEM/TLS.
  - Key disclosure; Mitigation: KMS/HSM, minimal key material in process, zeroization.
  - Replay/man-in-the-middle; Mitigation: unpredictable numbers, ARQC/ARPC validation.
  - UI spoofing; Mitigation: trusted UI path, PIN entry on secure pad.
- Residual risks: local debugging in dev builds; remove debug logs in production.

---

## 22. Detailed AC Sequences

- TC path (offline-approved):
  1) TAA requests TC → CAA `GENERATE AC` returns TC → `Completion`.
- ARQC path (online):
  1) TAA requests ARQC → CAA returns ARQC → Host auth → ARPC validation → Scripts → `Completion`.
- CDA (if enabled):
  - Combines DDA with cryptogram generation; verify CDA signature using ICC key during `GENERATE AC`.

---

## 23. Host Communication Abstraction

- Interface: `HostClient` (indicative): `AuthResponse authorize(AuthRequest req)`
- Responsibilities: pack/unpack (e.g., ISO 8583), keying, MAC, and TLS.
- Decouple from EMV phases by translating `EMV_Context` fields to host fields in an adapter.

---

## 24. Portability Matrix (Indicative)

- macOS (dev): clang++, POSIX I/O, software crypto → supported
- Linux: g++, PC/SC or vendor SDK → supported
- Windows: MSVC, winscard → requires adapter shims in `Runtime/`

---

## 25. Testing Strategy

- Unit tests: TLV parsing, DOL building, decision tables for TAA.
- Component tests: mock `SCRControl`, `UIControl`, `CryptoControl` to simulate flows.
- Integration tests: run scripted APDU traces and compare outcomes.
- Compliance: use scheme-provided test cards and host simulators.
- Tooling: enable sanitizers, static analysis, and CI builds across platforms.
