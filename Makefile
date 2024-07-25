CC=gcc
UTILS_DIR=../utils
CFLAGS=-Wall -Werror
CLIENT_DIR=client
SERVER_DIR=server

all: build-server build-client

build-client:
	@cd client && ${CC} ${CFLAGS} -o client *.c ${UTILS_DIR}/*.c


build-server:
	@cd server && ${CC} ${CFLAGS} -o server *.c ${UTILS_DIR}/*.c
