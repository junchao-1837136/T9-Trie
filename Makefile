CFLAGS = -Wall -g -std=c11

all: t9

t9: main.o trie.o
	gcc $(CFLAGS) -o $@ $^

trie.o: trie.c trie.h
	gcc $(CFLAGS) -o $@ -c $<

main.o: main.c trie.h
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -f t9 *.o