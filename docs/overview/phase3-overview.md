# Phase 3: Networking - Overview

**Duration:** May 2026 - Dec 2026 (~8 months, ~245 days)
**Work Schedule:** 1 hour/day average
**Total Hours Available:** ~245 hours

---

## Overview

Building network protocols from scratch. This phase progresses from DNS resolution to a complete TCP stack. Like previous phases, production code uses industry-standard libraries (STL, Boost, Folly, `absl`, libevent, etc.); Phase 1 data structures remain educational references only.

This phase establishes deep networking expertise that will be essential for the distributed systems capstone in Phase 4.

---

## Code Standards

All time estimates include:
- Project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`)
- Comprehensive unit testing (GoogleTest)
- Integration testing and protocol compliance testing
- Header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
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
  - Three-way handshake and connection management
  - Sliding window flow control
  - Congestion control (Reno, Cubic, BBR)
  - Packet reordering and retransmission
  - Benchmarks vs kernel TCP stack

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

