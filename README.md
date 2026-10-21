# mysocket

**mysocket** is a minimal C library that wraps the POSIX socket API for simple blocking TCP connections over IPv4.
It reduces the boilerplate of socket programming in C down to four calls: listen-and-accept, connect, write and read.

This library was created to reduce the boilerplate of socket programming in C, while keeping everything simple and hackable. It is used by my [FileTransfer](https://github.com/Gedankenn/FileTransfer) project.

---

## 🔧 Features

- ✅ Lightweight: one `.c` and one `.h`, no dependencies beyond libc
- 📡 Blocking TCP (IPv4) sockets
- 🖥️ Server side: `create_socket()` binds to `0.0.0.0:<port>`, listens and returns the accepted client's file descriptor
- 🔌 Client side: `connect_socket()` connects to a dotted-quad IPv4 address
- 🧠 Great for learning or quick prototyping

---

## 🗂️ Repository Structure

```
mysocket/
├── msocket.h          # Public API
├── msocket.c          # Implementation
├── examples/
│   ├── example.c      # Interactive server/client using the library
│   ├── server.c       # Standalone getaddrinfo() UDP echo server, IPv4/IPv6 (does not use the library)
│   └── client.c       # Matching UDP client (does not use the library)
├── makefile           # Builds examples/example
└── README.md
```

---

## 🚀 Quick Start

### 🔨 Build

```bash
git clone https://github.com/Gedankenn/mysocket.git
cd mysocket
make            # builds examples/example from examples/example.c + msocket.c
```

### ▶️ Run the example

```bash
./examples/example server 5555              # terminal 1
./examples/example client 5555 127.0.0.1    # terminal 2: type lines, the server prints them
```

---

## 🧪 Example Code

```c
#include "msocket.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    /* server: blocks until a client connects, returns the client's fd */
    int cfd = create_socket("5555");
    if (cfd < 0) return 1;

    char buf[BUF];
    int n = socket_read(cfd, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("got: %s\n", buf);
        socket_write(cfd, "ok", 2);
    }
    close(cfd);
    return 0;
}
```

---

## 📘 API Reference (`msocket.h`)

```c
int create_socket(char *port);
```
Creates a TCP socket, binds it to `0.0.0.0:<port>`, listens and **blocks until one client connects**. Returns the connected client's file descriptor, or `SOCKET_ERROR` (-1).

```c
int connect_socket(char *host, char *port);
```
Connects to `host` (IPv4 address string, e.g. `"192.168.0.10"`) on `port`. Returns the socket file descriptor, or `SOCKET_ERROR`.

```c
int socket_write(int sfd, void *data, int size);
```
Sends `size` bytes. Returns the number of bytes sent, or -1.

```c
int socket_read(int sfd, void *data, int buf_size);
```
Receives up to `buf_size` bytes into `data`. Returns the number of bytes read (0 when the peer closed), or -1.

Constants: `SOCKET_SUCCESS` (0), `SOCKET_ERROR` (-1), `BUF` (4096), `IPV4`/`IPV6` and `EXIT` (`"/-!EXIT!-/"`).

> IPv6 is not supported yet (the implementation uses `AF_INET`).

---

## 🛠️ Use in Your Project

Copy (or add as a git submodule) `msocket.c` and `msocket.h`, then compile them with your code:

```bash
gcc your_app.c msocket.c -I. -o your_app
```

---

## 🤝 Contributing

This is a personal utility project, but contributions are welcome.

- Found a bug? Open an issue.
- Have an idea? Open a discussion or PR.
- Want to use this in an embedded system or with non-blocking I/O? Fork away!

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 👤 Author

Developed by [Fabio Slika Stella](https://www.linkedin.com/in/fabio-slika-stella-6a37b513a/)  
Engineer passionate about C, Linux, embedded systems, and clean design.

---

## ⭐️ Show Support

If you find this project useful, give it a ⭐ on GitHub!
