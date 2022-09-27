# lib : Fichier Makefile
#
include ../Makefile.inc

LIBRARY=	$(PSE_LIB)/libpse.a
MODULES_SRC=	$(wildcard *.cpp)
MODULES_OBJ=	$(patsubst %.cpp,%.o,$(MODULES_SRC))

all: $(LIBRARY)

$(LIBRARY): $(MODULES_OBJ)
	rm -f $(LIBRARY)
	ar rs $(LIBRARY) $(MODULES_OBJ)
	rm -f $(MODULES_OBJ)

.cpp.o:
	g++ -c ${CFLAGS} $<

clean :
	rm -f $(MODULES_OBJ) $(LIBRARY) *~


