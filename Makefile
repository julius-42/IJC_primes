CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2


TARGETS = primes primes-i

.PHONY: all run clean


all: $(TARGETS)

primes: primes.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

primes-i: primes-i.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ $^ -lm

primes.o: primes.c bitarray.h
	$(CC) $(CFLAGS) -c primes.c -o $@

primes-i.o: primes.c bitarray.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o $@

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o $@

run: $(TARGETS)
	@printf -- "\n"
	@printf -- "\033[1;32m--- Running primes (makra) ---\033[0m\n"
	@ulimit -s 102400 && ./primes
	@printf -- "\n\033[1;32m--- Running primes-i (inline) ---\033[0m\n"
	@ulimit -s 102400 && ./primes-i


clean:
	rm -f *.o $(TARGETS)