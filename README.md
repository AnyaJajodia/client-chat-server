# Client-Chat-Server

**A lightweight, multi-user terminal-based chat system built in C**

## 📌 Overview

**Client-Chat-Server** is a simple yet robust client-server chat application that enables real-time messaging between multiple users via terminal. It uses sockets and `select()` to manage multiple client connections without threading, making it efficient and easy to understand.

### ✨ Features

- 🌐 Supports multiple simultaneous client connections (default: 3)
- 💬 Real-time text-based chat with user-friendly prompts
- 🔌 Reliable communication with custom message length encoding
- 🧹 Graceful connection handling and clean shutdowns
- ⚙️ Easy compilation via a single Makefile

---

## 🛠️ Project Structure

| File             | Description                                               |
|------------------|-----------------------------------------------------------|
| `chatserver.c`   | Server-side logic: manages clients, broadcasts messages   |
| `chatclient.c`   | Client-side logic: connects to server, sends/receives messages |
| `util.h`         | Shared utility functions for communication and parsing    |
| `Makefile`       | Simplifies compilation and execution                      |

---

## 🚀 Getting Started

### 🔧 Prerequisites

- GCC compiler (`gcc`)
- `make` utility
- Unix-based terminal (Linux, macOS)

---

### 🧱 Building the Project

Clone the repository and build the binaries:

```bash
git clone https://github.com/yourusername/client-chat-server.git
cd client-chat-server
make
```
<br>
This will generate: <br>

- `chatclient` <br>
- `chatserver` <br>

---

### 🖥️ Usage

**🟢 Start the Server**

```bash
./chatserver <port>
```

Example:

```bash
./chatserver 5000
```
<br>

**🔵 Start the Client(s)**

In another terminal window (or multiple terminals for multiple users):

```bash
./chatclient <server_ip> <port>
```

Example:

```bash
./chatclient 127.0.0.1 5000
```

Each client will be prompted to enter a username. Type your message and press Enter to chat. Type bye to exit.

---

### 📌 Notes

- Server supports up to 3 concurrent clients (MAX_CONNECTIONS in chatserver.c). You can increase this value if needed. <br>
- Messages are prefixed with usernames for clarity. <br>
- Uses select() to multiplex I/O for scalability without threads. <br>



