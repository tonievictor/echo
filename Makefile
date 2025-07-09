CC=gcc
CFLAGS=-Wall -Werror
CLIENT_DIR=client
SERVER_DIR=server

all: build-server build-client

build-client:
	@cd client && ${CC} ${CFLAGS} -o client *.c 


build-server:
	@cd server && ${CC} ${CFLAGS} -o server *.c 
