# Port Scanner

A C++ network port scanner for learning socket programming and networking fundamentals.

## 🎯 Current Features

**Working Implementation:**
- Multi-port TCP connection testing
- Predefined common service port scanning
- Clean output showing only open ports
- Proper socket lifecycle management
- Input validation and error handling

**Sample Output:**
```
 ___                  _         ___
| _ \   ___    _ _   | |_      / __|   __    __ _    _ _     _ _     ___    _ _
|  _/  / _ \  | '_|  |  _|     \__ \  / _|  / _` |  | ' \   | ' \   / -_)  | '_|
|_|    \___/  |_|     \__|     |___/  \__|  \__,_|  |_||_|  |_||_|  \___|  |_|

Enter target IP (or 'quit' / 'q' to exit): 127.0.0.1
[1] Quick Scan
[2] Custom Port Range
[3] Exit

Enter choice: 1

[Quick Scan] Scanning common ports...
Port 81 : CLOSED
Port 110 : CLOSED
Port 135 : OPEN
Port 143 : CLOSED
Port 443 : CLOSED
Port 445 : OPEN
```

---

## 🚀 Skills Demonstrated

- **Winsock API**: Socket creation, connection handling, cleanup
- **C++ STL**: Vector containers, range-based loops
- **Network Programming**: TCP connection testing, port enumeration
- **Resource Management**: Proper socket lifecycle and memory cleanup

---

## 🔧 Build & Run

**Requirements:**
- Windows 10/11
- g++ with C++17 support
- CMake 3.13+

**Build:**
```bash
mkdir build && cd build
cmake ..
cmake --build .
../port-scanner.exe
```