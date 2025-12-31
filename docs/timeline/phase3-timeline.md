# Phase 3: Networking - Detailed Timeline

**Duration:** May 2026 - Dec 2026 (~8 months, ~245 days)
**Work Schedule:** 1 hour/day average
**Total Hours Available:** ~245 hours

---

## Overview

Building network protocols from scratch. This phase progresses from DNS resolution to a complete TCP stack.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), integration testing and protocol compliance testing, and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

---

## Project List

**Network Protocols:**
- [ ] **DNS Server** - Caching resolver with ad-blocking | 30-40 hours | May-Jun 2026
- [ ] **UDP from Scratch** - Complete UDP protocol over raw sockets | 40-50 hours | Jun-Jul 2026
- [ ] **TCP from Scratch** ⭐⭐⭐ Capstone - Complete TCP with congestion control | 120-150 hours | Aug-Dec 2026

**Total Estimated Time:** ~190-240 hours

---

## Detailed Project Breakdown

### DNS Server (May-Jun 2026)

**Estimated:** 30-40 hours

**Components:**
- Recursive and iterative DNS resolution
- Caching with TTL support
- Ad-blocking using Bloom Filter from Phase 1
- UDP-based protocol implementation
- Testing with dig, nslookup

### UDP from Scratch (Jun-Jul 2026)

**Estimated:** 40-50 hours

**Components:**
- Complete UDP protocol over raw sockets
- Checksum validation (using CRC32 from Phase 1)
- Socket API design
- Packet fragmentation handling
- Testing with netcat, wireshark

### TCP from Scratch (Aug-Dec 2026) ⭐⭐⭐ Capstone

**Estimated:** 120-150 hours

**Components:**
1. Connection management (three-way handshake, teardown)
2. Sliding window flow control
3. Congestion control (Reno, Cubic, BBR)
4. Packet reordering and retransmission
5. Timeout and RTT estimation
6. Benchmarks vs kernel TCP stack

**Key Learnings:**
- Deep understanding of TCP protocol
- State machine implementation
- Performance optimization
- Real-world protocol testing

---

## Key Milestones

- **Jun 2026:** DNS Server complete
- **Jul 2026:** UDP from Scratch complete
- **Dec 2026:** TCP from Scratch complete ⭐⭐⭐

---

## Notes

- TCP from Scratch is the capstone project (4 months) - stands alone without additions
- DNS uses Bloom Filter from Phase 1 for ad-blocking
- UDP prepares for TCP complexity
- **BitTorrent and Custom Allocators moved to Phase 5 (optional projects)**
- Focus on depth (TCP protocol mastery)
- Skills from this phase enable the geo-distributed CDN in Phase 4
- Phase 3 completes in December 2026, leaving time before Phase 4 starts in April 2027

---

**Links:**
- [Phase 3 Overview](../overview/phase3-overview.md)
- [Back to README](../../README.md)
