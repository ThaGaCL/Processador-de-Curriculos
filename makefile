CFLAGS = -Wall
CC = gcc     
     
objects = main.o libdir.o libutil.o\
     
lattes: $(objects)
	$(CC) $(objects) -o lattes
    
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

libdir.o: libdir.c
	$(CC) -c libdir.c $(CFLAGS)

libutil.o: libutil.c
	$(CC) -c libutil.c $(CFLAGS)

clean:
	-rm -f lattes $(objects)

