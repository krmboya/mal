CFLAGS=-g -Wall -Wextra -rdynamic -DNDEBUG -Isrc $(OPTFLAGS)
LIBS= -ldl $(OPTLIBS) # ldl - library that allows for dynamic linking
PREFIX?=/usr/local # ?= - default value for PREFIX

SOURCES=$(wildcard src/**/*.c src/*.c) # dynamically assigns .c files under src
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))  # make a list of .o files from SOURCES

TEST_SRC=$(wildcard tests/*_tests.c)

# list of steps to build
STEPS=step0_repl step1_read_print

# list of tests to be executed
TESTS=

# These are just libraries, important targets are the actual steps
TARGET=build/libmal.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests steps

# Compilation rules for each of the steps
step0_repl: step0_repl.c $(TARGET)
	$(CC) $(CFLAGS) $@.c $(LIBS) $(TARGET) -o $@

step1_read_print: step1_read_print.c $(TARGET)
	$(CC) $(CFLAGS) $@.c $(LIBS) $(TARGET) -o $@

# redefine CFLAGS then target all
dev: CFLAGS=-g -Wall -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

# MAL steps
steps: $(STEPS)

# -fPIC generate position independent code, suitable for inclusion in libraries
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@ 

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests  # ignores the already existing directory to always run
tests: $(TESTS)
	sh ./tests/runtests.sh

# compilation rule for each test, includes static library
# position of TARGET is significant
tests/%_tests: tests/%_tests.c $(TARGET)
	$(CC) $(CFLAGS) $@.c $(LIBS) $(TARGET) -o $@

# Define VALGRIND the execute make again
valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(STEPS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok_)|stpn?cpy|a?sn?printf|byte_)'
# @ prefix - make only prints the relevant output, not command being executed
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
