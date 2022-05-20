build-lib: src/hashtable.c include/hashtable.h
	clear
	gcc -c -x c -std=c17 -Wall -Werror -Iinclude/ -O -fpic -o lib/libHashtable.so src/hashtable.c

build-tests: bin/hashtable.o
	clear
	gcc -x c -std=c17 -Wall -Werror -Iinclude/ -O -o bin/hashtable.tests tests/hashtable.tests.c -lm -Wl,bin/hashtable.o

bin/hashtable.o: src/hashtable.c include/hashtable.h
	clear
	gcc -c -x c -std=c17 -Wall -Werror -Iinclude/ -O -o bin/hashtable.o src/hashtable.c

run-tests:
	clear
	./bin/hashtable.tests
