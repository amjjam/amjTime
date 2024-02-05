FLAGS=-Wall -g -fPIC
CPPFLAGS=$(FLAGS)

AMJTIME_SRC=amjTime.C
AMJTIME_OBJ=$(AMJTIME_SRC:.C=.o)

CPP=g++ $(CPPFLAGS)

all: libamjTime.so

libamjTime.so: $(AMJTIME_OBJ)
	$(CPP) -shared -Wl,-soname,$@ -o $@ $^

install: libamjTime.so ../include/amjTime.H
	mkdir -p /opt/amj/lib
	mkdir -p /opt/amj/include
	cp libamjTime.so /opt/amj/lib
	cp ../include/amjTime.H /opt/amj/include

uninstall:
	- rm /opt/amj/lib/libamjTime.so
	- rm /opt/amj/include/amjTime.H

clean:
	- rm libamjTime.so $(AMJTIME_OBJ)
