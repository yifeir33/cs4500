CFLAGS= -O3 -Wall -std=c++11 -pthread

main: server client

server: server.o server_connection.o server_main.cpp netport.h
	clang++ $(CFLAGS) server_main.cpp server.o server_connection.o -o server

server.o: server.h server.cpp server_connection.o object.h array.h helper.h socket_addr.h util.h
	clang++ $(CFLAGS) -c server.cpp server_connection.o -o server.o

server_connection.o: server_connection.cpp thread.h object.h array.h queue.h helper.h packet.h socket_addr.h connection.h
	clang++ $(CFLAGS) -c server_connection.cpp -o server_connection.o

client: client_main.cpp client.o
	clang++ $(CFLAGS) client_main.cpp client.o -o client

client.o: client.h client.cpp helper.h array.h packet.h socket_addr.h connection.h ctc_connection.h cts_connection.h netport.h util.h
	clang++ $(CFLAGS) -c client.cpp -o client.o

.PHONY: clean
clean:
	rm *.o

run: server client
	./server -ip 127.0.0.1 &
	./client -ip 127.0.0.1 &
	./client -ip 127.0.0.1 &
