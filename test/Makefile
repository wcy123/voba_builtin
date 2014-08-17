CFLAGS += -I../src
TEST_FILES := $(wildcard test_*.c)
TESTS := $(patsubst %.c,%, $(TEST_FILES))
TEST_INPUTS :=$(patsubst %.c,%.in, $(TEST_FILES))
TEST_OUTPUTS :=$(patsubst %.c,%.out, $(TEST_FILES))

LDFLAGS += -L../src -L ../../voba_value/src  -L ../../voba_module/src  
LDFLAGS += -Wl,-rpath,../../voba_value/src/ -Wl,-rpath,../../voba_module/src/   -lvoba_value -lvoba_module

all: $(TESTS) $(TEST_OUTPUTS)

%.out: %.in  %
	./$(patsubst %.out,% , $@) < $(patsubst %.out,%.in, $@) > $@

test_module.out:
	./$(patsubst %.out,% , $@) < $(patsubst %.out,%.in, $@) > $@
%.out: %

%: %.c

clean:
	rm $(TESTS) $(TEST_OUTPUTS)

.PHONY: clean  test_module.out


