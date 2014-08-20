
INCLUDE += -I .
INCLUDE += -I ../exec_once
INCLUDE += -I ../voba_str
INCLUDE += -I ../voba_value
INCLUDE += -I ../voba_module
INCLUDE += -I ../../vhash
INCLUDE += -I ~/d/other-working/GC/bdwgc/include
GC_PATH := /home/chunywan/d/other-working/GC/bdwgc/mybuild
LIBS += -L $(GC_PATH)
CFLAGS   += $(INCLUDE)
CXXFLAGS += $(INCLUDE)
LDFLAGS  += $(LIBS)
LDFLAGS  += -Wl,-rpath,$(GC_PATH) -lgcmt-dll
LDFLAGS  += -ldl

FLAGS += -Wall -Werror

CFLAGS += -ggdb -O0
CFLAGS += -std=c99
CFLAGS += $(FLAGS)

CXXFLAGS += -std=c++11
CXXFLAGS += $(FLAGS)


CFLAGS += -fPIC

all: libvoba_builtin.so

libvoba_builtin.so: voba_builtin_module.o ../voba_module/voba_module.h ../voba_module/voba_module_end.h ../voba_value/voba_value.h ../voba_value/data_type_imp.h
	$(CXX) -shared -Wl,-soname,$@  -o $@ $<


clean:
	rm *.o *.so

.PHONY: all clean
