COMPILER = g++
CFLAGS = -Wall -std=c++11

docker: main.o sorer.o
	$(COMPILER) $(CFLAGS) -o sorer main.o sorer.o

main.o: main.cpp sorer.h
	$(COMPILER) $(CFLAGS) -c main.cpp

sorer.o: sorer.cpp sorer.h
	$(COMPILER) $(CFLAGS) -c sorer.cpp

clean:
	rm *.o
