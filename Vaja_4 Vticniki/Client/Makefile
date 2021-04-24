all: build run
build:
	gcc -Wall main.c -m32 -g -o demo_client -lcrypto -lssl
run:
	./demo_client
clean:
	rm -f demo_client