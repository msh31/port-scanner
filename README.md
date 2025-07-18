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
Enter target IP (or 'quit' / 'q' to exit): 127.0.0.1
Scanning 127.0.0.1...
Port 135 : OPEN
Port 445 : OPEN
Port 3389 : OPEN
Port 5357 : OPEN
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

---

## 📚 Development Roadmap

### ✅ Phase 1: Foundation (Complete)
- Multi-port TCP scanning
- Socket management
- Basic error handling

### 🔄 Phase 2: Enhanced Scanning
- Connection timeouts
- Threading for faster scans
- Port range selection

### 🎯 Phase 3: Advanced Features
- Service detection
- UDP scanning
- GUI interface
