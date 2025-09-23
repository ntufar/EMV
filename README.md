# EMV Terminal Application

A modular C++ implementation of an EMV terminal transaction engine. It orchestrates the complete EMV flow from application selection through transaction completion, designed for portability across card readers and UI environments via a service-oriented runtime layer.

---

## Key Features
- **Standards-based EMV flow**: Implements the EMV transaction phases: Application Initialization, Offline Data Authentication, Processing Restrictions, Cardholder Verification, Terminal Risk Management, Terminal Action Analysis, Card Action Analysis, Online Processing, Issuer Script Processing, and Completion.
- **Component-oriented services**: Abstracts card reader, cryptography, and UI via service interfaces managed by an `AccessManager` (see docs/architecture.md for details).
- **Data-centric context**: A shared `EMV_Context` holds all transaction state and allows phases to communicate safely and deterministically.
- **Portable runtime**: Runtime adapters in `Runtime/` provide integration points for platform services, hardware, and IPC.
- **Utility TLV/APDU tooling**: Helpers to compose, parse, and exchange APDUs and TLVs in `Utility/`.

---

## Repository Layout
- `emv.cpp`, `emv.h`: Entry and high-level terminal flow glue.
- `EMV_Library/`: Core transaction phases and EMV logic (C++).
  - `ApplicationInitialization.*`, `OfflineDataAuthentication.*`, `ProcessingRestrictions.*`, `CardholderVerification.*`, `TerminalRiskManagement.*`, `TerminalActionAnalysis.*`, `CardActionAnalysis.*`, `OnLineProcessing.*`, `IssuerScriptProcessing.*`, `Completion.*`, `EMV_Context.*`, `Context.*`.
  - `SDA_Data.*`, `SDADataRecov.*`, `SSADataRecov.*` for authentication support.
  - `ApplSelector.*` for application selection.
  - `scr_command.*` for card command helpers.
  - `Prompter.*` for UI prompting abstractions.
  - `emv_constants.h` shared constants.
- `Runtime/`: Adapters and platform/runtime integration (hardware, IPC, OS services).
- `Utility/`: TLV/APDU and general utilities: `APDU.*`, `C_APDU.*`, `R_APDU.*`, `tlv_*`, `DataObject.*`, `common_functions.*`.
- `kartek/`: RSA/C support and headers used by some crypto flows.
- `docs/`: Documentation including architecture overview.
- Build files: `Makefile` at project root and in `EMV_Library/`.

---

## Quick Start

### Prerequisites
- C++ compiler supporting C++11 or later (e.g., clang++, g++).
- Make (GNU make recommended).
- POSIX-like environment (tested on macOS). Linux should work with minor adjustments.
- Optional: OpenSSL or platform crypto if integrating custom cryptography (see Runtime integration notes).

### Build
From project root:
```bash
make
```
This will compile the core library and any binaries configured in the root `Makefile`. You can also build the library portion from `EMV_Library/`:
```bash
cd EMV_Library && make && cd -
```
Artifacts (binaries/libraries) depend on your platform-specific `Makefile` rules. If a shared library is produced (e.g., `libcryptocme2.so`), it will be placed in the project root or the library directory per the Makefile directives.

### Run
If the build produces a terminal emulator binary (e.g., `emv`), run:
```bash
./emv
```
If not produced by default, you can create your own small driver by linking against the EMV library (see "Minimal Driver Example").

---

## Minimal Driver Example
Below is a simplified example for embedding the EMV flow in your own program. Adapt the service registration and runtime integration to your environment.

```cpp
#include "emv.h"

int main() {
    // Initialize runtime and services (UI, SCR, Crypto) here
    // Configure AID(s), terminal capabilities, and transaction params

    // Kick off the EMV flow using the provided orchestration
    // Example: emv_run_transaction(amount, transactionType, currency);

    return 0;
}
```

Compile and link with objects from `EMV_Library/` and any runtime/service adapters you include.

---

## Configuration & Extensibility
- **AccessManager**: Centralized service loader/locator. Register implementations for:
  - `SCRControl` (smart card reader): card I/O and presence events
  - `UIControl` (user interaction): prompts, PIN entry, and messages
  - `CryptoControl` (RSA/DDA/SDA, secure hashing): cryptographic primitives
  - `ApplSelControl` (application selection): AID discovery and selection policy
- **EMV Parameters**: Set terminal capabilities, floor limit, action codes, and risk parameters through the context or configuration hooks.
- **Adding a new card reader**: Implement `SCRControl` and register it with `AccessManager`.
- **Supporting new payment schemes**: Provide new service implementations that conform to the same interfaces and register them.

Refer to `docs/architecture.md` for class relationships, lifecycle, and data flow.

---

## Development

### Code Style
- Maintain clear separation of concerns between phases.
- Keep the `EMV_Context` the single source of truth for transaction state.
- Prefer small, well-named functions and avoid deep nesting.

### Testing
- Unit tests can be added per module. Suggested layout: `tests/<module>_tests.cpp`.
- Use dependency inversion for services to allow mocking readers, UI, and crypto backends.

### Logging & Diagnostics
- Add structured logs at phase boundaries and key decision points (TAA, CAA, ODA).
- Include tags for PAN hash, AID, ATC, and AC types where allowed. Never log sensitive values (full PAN, full track data, full cryptograms, keys).

---

## Troubleshooting
- Build fails: run `make clean && make V=1` for verbose output; verify compiler and SDK versions.
- Linker errors for crypto: ensure the appropriate crypto backend is available or stubbed; check `kartek/` and any platform libs.
- Card not detected: verify `SCRControl` implementation and device permissions. Use a known-good AID and test card.
- DDA/SDA failures: confirm CA/Issuer/ICC key material and date ranges. See `SDA_Data.*` and `IccPKCertData.*`.

---

## Security Notes
- Do not hard-code production keys or sensitive parameters.
- Zeroize sensitive buffers where possible.
- Follow PCI DSS guidance for handling PAN, PIN, and keys. Never log secrets.

---

## License
If this repository is part of a proprietary system, consult the project owners for licensing terms. Otherwise, include an OSS license file as appropriate.

---

## Further Reading
- See `docs/architecture.md` for a deep dive into components, runtime, and data flow.
- EMVCo Specifications and Book 3 for transaction processing guidelines.
