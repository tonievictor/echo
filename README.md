## Usage

- Build the executable

```bash
git clone https://github.com/tonie-ng/socket-gc.git
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

- Next, create another client instance with your preferred username in a new terminal (up to ten).

```bash
cd client
./client <username>
```

- With the connection created, you can start sending messages via one client and the message would be broadcasted to the other client(s).

## Todo
- [x] Set the sockets to non-blocking mode.
- [x] Create broadcast and subscribe functionality.
- [x] Create exit functionality for the server.
- [x] Attach username to the client buffer.
