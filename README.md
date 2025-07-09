# Port Scanner

A high-performance network port scanner built in C++ for learning networking concepts and system programming.

## 🎯 Project Overview

Educational project exploring network programming fundamentals through progressive port scanning toolkit development. Demonstrates practical socket programming, multi-threading, and network security concepts.

**Skills Demonstrated:**
- Winsock API and network programming
- Multi-threaded concurrent processing  
- Socket management and error handling
- Performance optimization techniques

---

## 📚 Development Roadmap

### Phase 1: Foundation
- Single-port TCP connection testing
- Basic socket creation and RAII management
- Timeout and error handling

### Phase 2: Multi-Port Scanning  
- Sequential and concurrent port range scanning
- Thread pool optimization
- Progress reporting

### Phase 3: Advanced Features
- Service detection and banner grabbing
- Multiple scan types (SYN, UDP, stealth)
- Network range scanning (CIDR support)

### Phase 4: Professional Tools
- GUI interface development
- Configuration and reporting systems

---

## 🔧 Build Requirements

**Environment:**
- **Compiler**: g++ (MinGW-w64) with C++17 support
- **Platform**: Windows  
- **Libraries**: Winsock2

**Build:**
```bash
mkdir build && cd build
cmake ..
make
```

---

## ⚖️ Ethical Guidelines

**Approved Usage:**
- Educational networking exploration
- Testing on personal/owned networks and devices
- Authorized security research
- Portfolio development

**Important:** Only scan systems you own or have explicit permission to test. Comply with local laws and organizational policies.

---

## 🔗 Related Projects

**[Memory Analysis Toolkit](https://github.com/msh31/memory-analysis-toolkit)** - C++ process memory manipulation and reverse engineering tools

*Part of a comprehensive systems programming learning journey exploring both memory forensics and network security concepts.*