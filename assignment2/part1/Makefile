COMPILER=g++
CFLAGS=-Wall -std=c++11 -g

OBJECTS = object.h string.h

testArray: array.h $(OBJECTS) test-array.cpp
	$(COMPILER) $(CFLAGS) test-array.cpp -o test-array
	./test-array

testQueue: queue.h $(OBJECTS) test-queue.cpp
	$(COMPILER) $(CFLAGS) test-queue.cpp -o test-queue
	./test-queue

testMap: map.h $(OBJECTS) ./part2/test-map.cpp
	cp ./part2/test-map.cpp ./
	$(COMPILER) $(CFLAGS) test-map.cpp -o test-map
	./test-map

.PHONY: clean
clean:
