# Phase 3: Networking - Overview

**Duration:** May 2026 - Dec 2026 (~8 months, ~245 days)
**Work Schedule:** 1 hour/day average
**Total Hours Available:** ~245 hours
**Language:** C (POSIX API focus)

---

## Overview

Building network protocols from scratch using C to develop a deep understanding of the POSIX API. This foundational knowledge of POSIX networking primitives will be essential when working with C++ networking libraries like Boost.Asio in future projects and open source contributions.

This phase progresses from DNS resolution to a complete TCP stack, focusing on raw socket programming, system calls, and low-level protocol implementation. Unlike previous phases that used C++, Phase 3 uses pure C to master POSIX networking APIs (`socket()`, `bind()`, `listen()`, `accept()`, `select()`, `epoll`, etc.) before applying this knowledge to higher-level C++ abstractions.

---

## Code Standards

All time estimates include:
- Project setup (`.h`, `.c`, test files, `makefile`)
- Comprehensive unit testing (using a C testing framework)
- Integration testing and protocol compliance testing
- Header file documentation and proper code commenting
- Performance benchmarks where applicable

---

## Projects

**Network Protocols:**

- **DNS Server** (30-40 hours)
  - Recursive and iterative resolution
  - Caching with TTL
  - Ad-blocking using Bloom Filter from Phase 1
  - UDP-based protocol implementation

- **UDP from Scratch** (40-50 hours)
  - Complete UDP protocol over raw sockets
  - Checksum validation (using CRC32 from Phase 1)
  - Socket API design
  - Testing with standard tools (netcat, wireshark)

- **TCP from Scratch** ⭐⭐⭐ (120-150 hours)
  - Built from [Level-IP](https://github.com/saminiir/level-ip) by Sami Niiranen
  - Linux userspace TCP/IP stack using TUN/TAP devices
  - Focus on understanding rather than implementation from scratch
  - Accompanied by [blog series](http://www.saminiir.com/lets-code-tcp-ip-stack-1-ethernet-arp) explaining the implementation
  - Study: Three-way handshake and connection management
  - Study: Sliding window flow control
  - Study: Congestion control and retransmission
  - Study: Socket API implementation
  - Benchmarks vs kernel TCP stack
  - Deep dive into POSIX networking APIs and TCP internals

**Total Estimated Time:** ~190-240 hours
**Available Time:** ~245 days × 1 hour/day = ~245 hours

> **Note:** BitTorrent Client and Custom Memory Allocators moved to Phase 5 (optional projects after graduation).

---

## Key Milestones

- **May-Jun 2026:** DNS Server
- **Jun-Jul 2026:** UDP from Scratch
- **Aug-Dec 2026:** TCP from Scratch (4 months) ⭐⭐⭐

---

## Key Learning Outcomes

- Deep understanding of network protocols (UDP, TCP, DNS)
- Socket programming and raw packet manipulation
- Congestion control and flow control algorithms
- Real-world protocol testing and compliance
- Performance benchmarking and optimization

---

## Links

- [Phase 3 Timeline](../timeline/phase3-timeline.md)
- [Back to README](../../README.md)

