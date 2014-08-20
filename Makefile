PREFIX  = ../build
INCLUDE += -I .
INCLUDE += -I ../exec_once
INCLUDE += -I ../voba_str
INCLUDE += -I ../../vhash
INCLUDE += -I ~/d/other-working/GC/bdwgc/include
INCLUDE += -I $(PREFIX)


CFLAGS   += $(INCLUDE)
CXXFLAGS += $(INCLUDE)

FLAGS += -Wall -Werror
FLAGS += -fPIC

CFLAGS += -ggdb -O0
CFLAGS += -std=c99
CFLAGS += $(FLAGS)


CFLAGS += -fPIC

all: install


install: libvoba_builtin.so
	install libvoba_builtin.so $(PREFIX)/voba/core/
	install builtin.h $(PREFIX)/voba/core/

libvoba_builtin.so: voba_builtin_module.o
	$(CXX) -shared -Wl,-soname,$@  -o $@ $<

clean:
	rm *.o *.so

.PHONY: all clean
