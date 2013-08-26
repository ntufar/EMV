PCSC_INCLUDE = ../../pcsc/src/

CFLAGS = -I$(PCSC_INCLUDE) -g 
CPPFLAGS = -I$(PCSC_INCLUDE) -g

OBJS = ApplSelector.o ApplicationInitialization.o CardActionAnalysis.o CardholderVerification.o Completion.o \
	CVM_List.o EMV_Context.o IccPKCertData.o ProcessingRestrictions.o Prompter.o IPKCertData.o Referral.o \
	scr_command.o scsEMV.o SDA_Data.o TerminalRiskManagement.o Context.o CVM_Rules.o dol_parser.o \
	IssuerScriptProcessing.o OfflineDataAuthentication.o OnLineProcessing.o ReadApplicationData.o \
	SDADataRecov.o SSADataRecov.o TerminalActionAnalysis.o TransactionDecision.o

all: $(OBJS)
	$(AR) crs libEMV.a $(OBJS) 
clean:
	rm -f *.o libEMV.a
