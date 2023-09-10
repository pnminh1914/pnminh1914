dict2: program2.o data.o array.o 
	gcc -o dict2 program.o data.o array.o

dict3: program3.o data.o tree.o 
	gcc -o dict3 program.o data.o tree.o 

program2.o: program2.c data.o array.o 
	gcc -c program2.c 

program3.o: program3.c data.o tree.o 
	gcc -c program3.c 

data.o: data.c data.h
	gcc -c data.c data.h
	
array.o: array.c array.h
	gcc -c array.c array.h

tree.o: tree.c tree.h
	gcc -c tree.c tree.h

clean:
	rm -f $(OBJ) $(EXE)
