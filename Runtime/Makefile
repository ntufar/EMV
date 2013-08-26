PCSC_INCLUDE = ../../pcsc/src/
OBJS = EventAdder.o   RSAPublicKey.o ServiceInterface.o \
	SCRControl_Interface.o SCRControlInterface.o SCROperationEvent.o \
	SCROperationEventImpl.o SCRInterface.o SCRControlImpl.o PINInterface.o \
	PINOperationEvent.o PINControl_Server.o PINOperationEventImpl.o \
	PINControlImpl.o HostControl_Server.o HostControlImpl.o \
	POSControl.o POSControl_Interface.o \
	POSControlVSDCImpl.o POSInterface.o POSOperationEvent.o POSControlVSDC.o POSOperationEventImpl.o \
	UIOperationEventImpl.o UIInterface.o UIOperationEvent.o \
	AccessManager.o amAdder.o ApplSelControlImpl.o\
	ApplSelInterface.o ApplSelOperationEvent.o ApplSelOperationEventImpl.o \
	CLCInterface.o CLCOperationEvent.o \
	CLCOperationEventImpl.o clcVSDCImpl.o CnfgInterface.o \
	CnfgOperationEvent.o CnfgOperationEventImpl.o \
	CnfgControlImpl.o CryptoInterface.o CryptoOperationEvent.o CryptoOperationEventImpl.o CryptoControlImpl.o \
	HostInterface.o HostOperationEvent.o HostOperationEventImpl.o OperationEvent.o OperationEventWithValue.o \
	RefInterface.o RefOperationEvent.o RefOperationEventImpl.o  \
	RefControlImpl.o SystemInterface.o SystemOperationEvent.o \
	SystemOperationEventImpl.o SystemControlImpl.o ServiceControl.o \
	UIControlImpl.o 

#removed: 
CFLAGS = -I$(PCSC_INCLUDE) -I$(CRYPTOLIB_INCLUDE) -g
CPPFLAGS = -I$(PCSC_INCLUDE) -I$(CRYPTOLIB_INCLUDE) -g
#RSA dependent 
#CryptoControlServer.o
#Windows dependent:
# CryptoControlInterface.o
all: $(OBJS)
	ar crs libRuntime.a $(OBJS)
ctags:
	ctags *
clean:
	rm -f *.o libRuntime.a
