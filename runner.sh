#!/usr/bin/env bash

gcc -Wall -Werror -o ./server/server ./server/*.c ./utils/*.c
gcc -Wall -Werror -o ./client/client ./client/*.c ./utils/*.c
