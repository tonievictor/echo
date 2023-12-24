# Socket GC

A CLI appliocation that enables multiple clients to communicate seamlessly on a shared server, offering real-time group conversations.

## Getting Started

```bash
git clone https://github.com/Tonie-NG/socket-gc.git
cd socket-gc
./runner.sh
```

## Usage

1. Build the executable

```bash
git clone https://github.com/Tonie-NG/socket-gc.git
cd socket-gc
./runner.sh
```

2. Run the server.

```bash
cd server
./server
```

3. On another terminal, run the client with your preferred username to connect to the server.

```bash
cd client
./client <username>
```

4. Next create another client instance with your preferred username in a new terminal. (as many clients as you want).

```bash
cd client
./client <username>
```

5. With the connection created, you can start sending messages via one client and the message would be broadcasted to the other client.
