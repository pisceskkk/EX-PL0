PL.exe: PL.o set.o io.o
	g++ -g -o PL.exe PL.o set.o io.o
 
PL.o: PL.cpp ptoc.h io_cpp.h io.h array.h varing_string.h set.h set_cpp.h
	g++ -c PL.cpp
 
set.o: set.c ptoc.h io_cpp.h io.h array.h varing_string.h set.h set_cpp.h
	gcc -c set.c

io.o: io.c ptoc.h io_cpp.h io.h array.h varing_string.h set.h set_cpp.h
	gcc -c io.c
.PHONY:clean 
clean:
	rm -f *.o
