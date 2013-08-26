PCSC_INCLUDE = ../pcsc/src/
CRYPTOLIB_INCLUDE = ../cryptolib/
CFLAGS = -I$(PCSC_INCLUDE) -I$(CRYPTOLIB_INCLUDE) -g
CPPFLAGS = -I$(PCSC_INCLUDE) -I$(CRYPTOLIB_INCLUDE) -g

RUNTIME_OBJS = $(patsubst %.cpp,%.o,$(wildcard Runtime/*.cpp))
EMV_OBJS = $(patsubst %.cpp,%.o,$(wildcard EMV_Library/*.cpp))
UTILITY_OBJS = $(patsubst %.cpp,%.o,$(wildcard Utility/*.cpp))
#CRYPTO_OBJS = $(patsubst %.cpp,%.o,$(wildcard Crypto/*.cpp))
CRYPTO_OBJS = $(patsubst %.cpp,%.o,$(wildcard ../cryptolib/*.c))


all: emv

emv: emv.o $(RUNTIME_OBJS) $(EMV_OBJS) $(UTILITY_OBJS) 
	make -C ../cryptolib/
	g++ -g -o emv emv.o $(RUNTIME_OBJS) $(EMV_OBJS) $(UTILITY_OBJS)   ../cryptolib/static-obj/*o -L../cryptolib/ -L../pcsc/src/ -LRuntime/RSA  -lpcsclite -lcryptocme_fips140 -lresolv -lpthread
#	make -C Utility
#	make -C EMV_Library
#	make -C Runtime
#	g++ -g -o emv -L../pcsc/src/ -LUtility/ -LEMV_Library/ -LRuntime/ emv.o -lUtility -lEMV -lRuntime -lUtility -lRuntime -lpcsclite $(RUNTIME_OBJS)

	
doc: 
	doxygen

clean:
	make -C Utility clean
	make -C EMV_Library clean
	make -C Runtime clean
	make -C ../cryptolib/ clean
	rm -f emv.o emv
