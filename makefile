MyGlobe:Countries.o KeyValuePair.o LinkedList.o HashTable.o Main.o
	gcc Countries.o KeyValuePair.o LinkedList.o HashTable.o Main.o -o MyGlobe	
Countries.o: Countries.c Countries.h Defs.h
	gcc -c Countries.c
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
Main.o: Main.c Countries.h Defs.h HashTable.h KeyValuePair.h
	gcc -c Main.c
