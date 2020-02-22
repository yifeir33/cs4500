CFLAGS = -pthread -std=c++11 -O0

bench: bench.cpp modified_dataframe.h txt_reader.h
	clang++ $(CFLAGS) bench.cpp -o bench

run:
	curl -L https://raw.githubusercontent.com/yifeir33/cs4500/master/assignment5/part1/datafile.txt > ./datafile.txt
	./bench
