all:
	gcc -o reader FredReader.c
	gcc -o writer FredWriter.c
clean:
	rm -f *.o *` core reader writer
