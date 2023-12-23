#!/usr/bin/env bash


gcc -o ./server/server ./server/*.c ./utils/*.c
gcc -o ./client/client ./client/*.c ./utils/*.c
