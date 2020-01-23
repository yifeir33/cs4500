
docker: main.o sorer.o
	g++ -Wall -std=c++11 -g -o sorer main.o sorer.o

main.o: main.cpp sorer.h
	g++ -Wall -std=c++11 -g -c main.cpp

sorer.o: sorer.cpp sorer.h
	g++ -Wall -std=c++11 -g -c sorer.cpp

clean:
	rm main.o
	rm sorer.o
