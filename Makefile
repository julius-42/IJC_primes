CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2

TARGETS = primes primes-i no_comment

.PHONY: all run clean


all: $(TARGETS)

primes: primes.o eratosthenes.o bitarray.o errors.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

primes-i: primes-i.o eratosthenes-i.o bitarray-i.o errors.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ $^ -lm

no_comment: no_comment.o errors.o
	$(CC) $(CFLAGS) -o $@ $^


primes.o: primes.c bitarray.h eratosthenes.h
	$(CC) $(CFLAGS) -c primes.c -o $@

primes-i.o: primes.c bitarray.h eratosthenes.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o $@


eratosthenes.o: eratosthenes.c eratosthenes.h bitarray.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o $@

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitarray.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o $@


no_comment.o: no_comment.c errors.h
	$(CC) $(CFLAGS) -c no_comment.c -o $@


bitarray.o: bitarray.c bitarray.h
	$(CC) $(CFLAGS) -c bitarray.c -o $@

bitarray-i.o: bitarray.c bitarray.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitarray.c -o $@


error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o $@


run: $(TARGETS)
	@printf -- "\n"
	@printf -- "\033[1;32m--- Running primes (macros) ---\033[0m\n"
	@ulimit -s 102400 && ./primes
	@printf -- "\n\033[1;32m--- Running primes-i (inline) ---\033[0m\n"
	@ulimit -s 102400 && ./primes-i


clean:
	rm -f *.o $(TARGETS)