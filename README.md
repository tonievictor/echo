## Usage
- Build the executable
> Install the make program before you proceed ie. `sudo apt install make`

```bash
# Build all components together
make all

# Build the client application
make client

# Build the server application
make server
```

- Run the server.

```bash
cd server
./server
```

- On different terminals, run the following to create multiple client instances (up to ten)

```bash
cd client
./client <username>
```

- With the connection created, you can start sending messages via one client and the message would be broadcasted to the other client(s).
