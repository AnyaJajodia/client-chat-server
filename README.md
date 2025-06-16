# CLIENT-CHAT-SERVER

_Empowering Seamless Connections for Real-Time Communication_

## Table of Contents

• [Overview](#overview) <br>
• [Getting Started](#getting-started) <br>
&nbsp;&nbsp;&nbsp;&nbsp;•[Prerequisites](#prerequisites)  <br>
&nbsp;&nbsp;&nbsp;&nbsp;•[Installation](#installation)  <br>
&nbsp;&nbsp;&nbsp;&nbsp;•[Usage](#usage)  <br>
&nbsp;&nbsp;&nbsp;&nbsp;•[Testing](#testing)  <br>

## Overview

client-chat-server is a versatile framework for developing real-time, multi-user chat applications. It combines core server and client components with utility functions to ensure reliable data exchange and input validation.

**Why client-chat-server?**

This project streamlines the development of networked chat systems by providing:

• 🛠️ Utility Functions: Standardized methods for safe message transmission and robust input parsing, reducing common communication errors.
• 🌐 Multi-Client Server: Handles multiple simultaneous connections, manages user sessions, and broadcasts messages efficiently.
• 💬 Real-Time Messaging: Facilitates seamless, bidirectional communication between clients and the server.
• 🚀 Automated Build: Simplifies compilation and deployment with a well-defined Makefile, ensuring consistency across environments.
• 🔒 Connection Stability: Implements graceful shutdowns and resource management for reliable operation.

## Getting Started

### Prerequisites

This project requires the following dependencies:
• **Programming Language**: C
• **Package Manager**: Make

### Installation

Build client-chat-server from the source and install dependencies:

1. **Clone the repository:**
```
❯ git clone https://github.com/AnyaJajodia/client-chat-server
```

2. **Navigate to the project directory:**
```
❯ cd client-chat-server
```

3. **Install the dependencies:**

**Using make:**
```
❯ make deps
```

### Usage

Run the project with:

Using make:
```
make run
```

### Testing

Client-chat-server uses the **{test_framework}** test framework. Run the test suite with:

Using make:
```
make test
```
