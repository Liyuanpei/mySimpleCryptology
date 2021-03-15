test: Cryptology.o
	gcc -o Cryptology Cryptology.o -lm
Cryptology.o: Cryptology.cpp stdafx.h DesCODE.h stdafx_data.h
	gcc -c Cryptology.cpp
clean: 
	rm *.o Cryptology

