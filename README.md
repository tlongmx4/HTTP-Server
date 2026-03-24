# TinCanHTTP

A lightweight HTTP server built from scratch in C using raw POSIX sockets. No frameworks, no libraries — just syscalls and stubbornness.

## Features

- TCP socket server listening on port 8080
- Route table with function pointer dispatch
- Serves multiple pages: index, about, contact, and 404
- Persistent connection loop for handling multiple requests
- Clean error handling on socket, bind, and accept

## Build

```bash
gcc -o server main.c
```

## Run

```bash
./server
```

Then visit `http://localhost:8080` in your browser.

## Routes

| Path | Handler | Description |
|------|---------|-------------|
| `/` | `server_index_page` | Home page |
| `/about` | `server_about_page` | About page |
| `/contact` | `server_contact_page` | Contact page |
| `*` | `server_404_page` | 404 fallback |

## How It Works

The server follows the standard POSIX socket lifecycle:

1. `socket()` — create a TCP socket
2. `bind()` — attach to `INADDR_ANY:8080`
3. `listen()` — mark as passive
4. `accept()` — block until a client connects
5. `read()` — pull the raw HTTP request
6. Route matching — `sscanf` parses the method and path, then a loop through the route table finds the right handler
7. `write()` — send back an HTTP response
8. `close()` — clean up the client connection
9. Loop back to step 4

## License

Do whatever you want with it.