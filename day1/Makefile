CC := clang

CFLAGS := -Wall -Wpedantic

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
EXE := solution

.PHONY: all clean

all: $(EXE)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(EXE): $(OBJS)
	$(CC) $^ -o $@

clean:
	rm -f *.o $(EXE)
