exe: servidor.o
	g++ -o exe servidor.o
servidor.o: servidor.cpp
	g++ -Wall -c servidor.cpp
clean:
	rm exe servidor.o