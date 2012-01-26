make: servant.c central.c servant.h central.h
	gcc -Wall -o Client servant.c
	gcc -Wall -o Server central.c
