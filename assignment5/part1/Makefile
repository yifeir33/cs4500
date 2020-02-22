CFLAGS = -pthread -std=c++11 -O0

bench: bench.cpp modified_dataframe.h txt_reader.h
	clang++ $(CFLAGS) bench.cpp -o bench

test:
	./bench
