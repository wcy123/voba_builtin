CFLAGS += -fPIC

all: libvoba_builtin.so

libvoba_builtin.so: voba_builtin_module.o ../../voba_module/src/voba_module.h ../../voba_module/src/voba_module_end.h
	$(CXX) -shared -Wl,-soname,$@  -o $@ $<


clean:
	rm *.o *.so

.PHONY: all clean
