# mysocket

**mysocket** is a minimal C library that wraps the low-level socket API in a clean, reusable interface.  
It simplifies the creation of client-side network connections using IPv4 or IPv6 with blocking I/O, providing just the essentials to get connected and communicate.

This library was created to reduce the boilerplate of socket programming in C, while keeping everything simple, portable, and hackable.

---

## 🔧 Features

- ✅ Lightweight, no dependencies
- 🌐 IPv4 and IPv6 support
- 📡 Blocking TCP socket operations
- 🧼 Clean abstraction with `Socket` struct
- 🧠 Great for learning or quick prototyping

---

## 🗂️ Repository Structure

```
mysocket/
├── include/
│   └── mysocket.h        # Public API
├── src/
│   └── mysocket.c        # Implementation
├── main.c                # Example client
├── Makefile              # Build system
└── README.md             # This file
```

---

## 🚀 Quick Start

### 🔨 Build

```bash
git clone https://github.com/Gedankenn/mysocket.git
cd mysocket
make
```

This will compile `main.c` and link against your `mysocket` implementation, producing a test client binary.

---

## 🧪 Example Code

Here's a complete example using the `mysocket` API to connect to a server and print the response:

```c
#include "mysocket.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    Socket s;

    if (socket_open(&s, SOCK_STREAM) < 0) {
        perror("socket_open");
        return 1;
    }

    if (socket_connect(&s, "example.com", "80") < 0) {
        perror("socket_connect");
        socket_close(&s);
        return 1;
    }

    const char *msg = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
    socket_send(&s, msg, strlen(msg));

    char buffer[1024];
    ssize_t received = socket_recv(&s, buffer, sizeof(buffer) - 1);
    if (received > 0) {
        buffer[received] = '\0';
        printf("Received:\n%s\n", buffer);
    }

    socket_close(&s);
    return 0;
}
```

---

## 📘 API Reference

```c
int socket_open(Socket *s, int type);
```
Initializes the socket with the given type (e.g., `SOCK_STREAM`).

```c
int socket_connect(Socket *s, const char *host, const char *port);
```
Connects the socket to the given host and port.

```c
ssize_t socket_send(Socket *s, const void *buf, size_t len);
```
Sends data through the socket.

```c
ssize_t socket_recv(Socket *s, void *buf, size_t len);
```
Receives data from the socket.

```c
void socket_close(Socket *s);
```
Closes the socket and cleans up resources.

---

## 🛠️ Use in Your Project

You can include the library in your own C projects like this:

```bash
gcc your_app.c src/mysocket.c -Iinclude -o your_app
```

Or compile as a static library and link separately:

```bash
make lib
# Produces build/libmysocket.a
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
