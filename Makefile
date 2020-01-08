
all: frequency trie.o

frequency:trie.o 
	gcc -Wall -g -o frequency trie.o

trie.o: trie.c trie.h
	gcc -Wall -g -c trie.c

.PHONY: clean all 

clean:
	rm -f *.o frequency

