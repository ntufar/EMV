CPPFLAGS = -g
OBJS = APDU.o C_APDU.o common_functions.o DataObject.o Language.o R_APDU.o tlv.o tlv_creator.o tlv_parser.o
all: $(OBJS)
	$(AR) crs libUtility.a $(OBJS) 
clean:
	rm -f *.o libUtility.a
