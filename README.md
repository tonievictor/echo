# Socket GC

A CLI appliocation that enables multiple clients to communicate on a shared server.

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

- Next create another client instance with your preferred username in a new terminal. (as many clients as you want).

```bash
cd client
./client <username>
```

- With the connection created, you can start sending messages via one client and the message would be broadcasted to the other client.
