CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE
CC = gcc     
     
objects = main.o libdir.o libutil.o libstruct.o edit-distance.o\
     
lattes: $(objects)
	$(CC) $(objects) -o lattes
    
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

libdir.o: libdir.c
	$(CC) -c libdir.c $(CFLAGS)

libutil.o: libutil.c
	$(CC) -c libutil.c $(CFLAGS)

libstruct.o: libstruct.c
	$(CC) -c libstruct.c $(CFLAGS)

edit-distance.o: edit-distance.c
	$(CC) -c edit-distance.c $(CFLAGS)

clean:
	-rm -f lattes $(objects)

