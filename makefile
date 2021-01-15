all: frequency

frequency: frequency.c
	gcc -Wall -g frequency.c -o frequency

clean:
	rm frequency

.PHONY: all clean