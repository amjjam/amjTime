prefix=/opt/amj

FLAGS=-Wall -g -fPIC
CPPFLAGS=$(FLAGS)

AMJTIME_SRC=amjTime.C
AMJTIME_OBJ=$(AMJTIME_SRC:.C=.o)

CPP=g++ $(CPPFLAGS)

all: libamjTime.so

libamjTime.so: $(AMJTIME_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^

install: libamjTime.so ../include/amjTime.H
	mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/include
	cp libamjTime.so $(prefix)/lib
	cp ../include/amjTime.H $(prefix)/include

uninstall:
	- rm $(prefix)/lib/libamjTime.so
	- rm $(prefix)/include/amjTime.H

clean:
	- rm libamjTime.so $(AMJTIME_OBJ)
