exe: servidor.o
	g++ -o exe servidor.o -lpthread
servidor.o: servidor.cpp servidor.h
	g++ -c servidor.cpp
clean:
	rm exe servidor.o
