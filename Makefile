
all: frequency trie.o

frequency:trie.o 
	gcc -Wall -o frequency trie.o

trie.o: trie.c trie.h
	gcc -Wall -c trie.c

.PHONY: clean all 

clean:
	rm -f *.o frequency

