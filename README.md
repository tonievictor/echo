This project is a work in progress and a learning experience inspired by [Socket Programming in C](https://www.youtube.com/watch?v=KEiur5aZnIM&t=1192s)

## Usage

- Build the executable

```bash
git clone https://github.com/Tonie-NG/socket-gc.git
cd socket-gc
./runner.sh
```

- Run the server.

```bash
cd server
./server
```

- On another terminal, run the client with your preferred username to connect to the server.

```bash
cd client
./client <username>
```

- Next, create another client instance with your preferred username in a new terminal. (as many clients as you want).

```bash
cd client
./client <username>
```

- With the connection created, you can start sending messages via one client and the message would be broadcasted to the other client.

## Todo
- [x] Create broadcast and subscribe functionality.
- [x] Create exit functionality for the server.
- [ ] Set the sockets to non-blocking mode.
