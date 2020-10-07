all: run_all

run_all: run_server run_client

run_server: build_server
	./server &

run_client: build_client
	./client

build_server:
	gcc server.c -o server -Wall -Wextra

build_client:
	gcc client.c -o client -Wall -Wextra

check: run_all 
	@bash script.sh

clean:
	-rm client server
