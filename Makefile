CC = gcc

CFLAGS = -g

MAINOBJS = main.o function_scan.o

scanner: $(MAINOBJS)
	$(CC) $(CFLAGS) $(MAINOBJS) -o scanner

.PHONY: clean

clean:
	rm -f scanner *.o
