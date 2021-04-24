all: build run
build:
	gcc -Wall main.c -m32 -g -o demo_server -lcrypto -lssl
run:
	./demo_server
clean:
	rm -f demo_server