CFLAGS += -fPIC

all: libvoba_builtin.so

libvoba_builtin.so: voba_builtin_module.o ../src/voba_macros.h
	$(CXX) -shared -Wl,-soname,$@  -o $@ $<


clean:
	rm *.o *.so

.PHONY: all clean
