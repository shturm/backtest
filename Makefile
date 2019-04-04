CC=gcc
AR ?= ar
RANLIB ?= ranlib

#CCFLAGS ?= -Wall -Wextra -Wshadow -Wconversion -O2 -g
CCFLAGS ?=-g
CCLINK=-I"vendor/tulipindicators" -L"vendor/tulipindicators" -lindicators
CCLINK+=-I"./" -L"./" -lbacktest

#SRCS=$(wildcard indicators/*.c)
#OBJS=$(SRCS:%.c=%.o)

TESTSRCS=$(wildcard tests/*.c)
TESTOBJS=$(TESTSRCS:%.c=%.out)
TESTOBJSBUILT=$(wildcard tests/*.o)

#.SUFFIXES: .c .o .h .ca

all: libbacktest.a backtest tests example-strategy-empty example-strategy

backtest:
	$(CC) backtest-exec.c backtest.c history.c -L"./" -lbacktest -o backtest

libbacktest.a:
	$(CC) -c $(CCFLAGS) backtest.c $(CCLINK) -o backtest.o
	$(CC) -c $(CCFLAGS) history.c $(CCLINK) -o history.o
	$(AR) rcu $@ backtest.o history.o
	$(RANLIB) $@

tests: libbacktest.a $(TESTOBJS)

example-strategy-empty:
	$(CC) $(CCFLAGS) examples/example-strategy-empty.c -I"./" -L"./" -lbacktest $(CCLINK) -o examples/example-strategy-empty.out

example-strategy:
	$(CC) $(CCFLAGS) examples/example-strategy.c -I"./" -L"./" -lbacktest $(CCLINK) -o examples/example-strategy.out

runtests:
	sh run-tests.sh

clean:
	rm -f backtest
	rm -f *.a
	rm -f *.exe
	rm -f *.o
	rm -f tests/*.o
	rm -f tests/*.out
	rm -f tests/output/*
	rm -f examples/*.o
	rm -f examples/*.out

.c.out:
#$(CC) -c $(CCFLAGS) $< -o $@
	$(CC) $(CCFLAGS) $< $(CCLINK) -o $@
