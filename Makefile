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

ifneq ($(CONFIG),release)
	CFLAGS += -ggdb -O0
	CXXFLAGS += -ggdb -O0
else
	CFLAGS += -O3 -DNDEBUG
	CXXFLAGS += -O3 -DNDEBUG
endif

CFLAGS += -std=c99
CFLAGS += $(FLAGS)


CFLAGS += -fPIC

all: install

C_SRCS += builtin.c
C_SRCS += gf.c
C_SRCS += integer.c
C_SRCS += range.c
C_SRCS += print.c
C_SRCS += array.c
C_SRCS += match.c
C_SRCS += str.c
C_SRCS += other.c


OBJS += $(patsubst %.c,%.o,$(C_SRCS))

libvoba_builtin.so: $(OBJS)
	$(CC) -shared -Wl,-soname,$@  -o $@ $+

clean:
	rm *.o *.so

.PHONY: all clean




INSTALL_FILES += $(PREFIX)/voba/core/libvoba_builtin.so
INSTALL_FILES += $(PREFIX)/voba/core/builtin.h
install: $(INSTALL_FILES)

$(PREFIX)/voba/core/libvoba_builtin.so :  libvoba_builtin.so
	install libvoba_builtin.so $(PREFIX)/voba/core/
$(PREFIX)/voba/core/builtin.h :  builtin.h
	install builtin.h $(PREFIX)/voba/core/



.PHONY: depend
depend: 
	for i in $(C_SRCS); do $(CC) -MM $(CFLAGS) $$i; done > $@.inc

-include depend.inc

test:
	echo $(OBJS)
