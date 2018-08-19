EXE=wiked

CC=gcc
CFLAGS= -Wall -g

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)
