COMPILER = g++
CFLAGS = -Wall -std=c++11

docker: main.o sorer.o
	$(COMPILER) $(CFLAGS) -o sorer main.o sorer.o

main.o: main.cpp sorer.h
	$(COMPILER) $(CFLAGS) -c main.cpp

sorer.o: sorer.cpp sorer.h
	$(COMPILER) $(CFLAGS) -c sorer.cpp

test_sorer.o: test_sorer.cpp sorer.h
	$(COMPILER) $(CFLAGS) -c test_sorer.cpp

sorer_unit_tests: test_sorer.o sorer.o
	$(COMPILER) $(CFLAGS) -o sorer_unit_tests test_sorer.o sorer.o

clean:
	rm *.o
	rm sorer_unit_tests

test: sorer_unit_tests SORfile
	./sorer -f "SORfile" -from 0 -len 100 -print_col_type 0
	./sorer -f "SORfile" -from 0 -len 100 -print_col_type 2
	./sorer -f "SORfile" -from 0 -len 100 -is_missing_idx 2 0
	./sorer -f "SORfile" -from 0 -len 100 -is_missing_idx 2 1
	./sorer -f "SORfile" -from 0 -len 100 -is_missing_idx 2 2
	./sorer -f "SORfile" -from 0 -len 100 -print_col_idx 2 0
	./sorer -f "SORfile" -from 5 -len 100 -print_col_idx 1 0
	./sorer_unit_tests
