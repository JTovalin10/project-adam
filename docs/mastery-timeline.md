# Phase 2: Evolution - Network and Concurrency - Detailed Timeline

**Duration:** Mar 2026 - Dec 2026 (10 months, ~305 days)  
**Work Schedule:** 1 hour/day average  
**Total Hours Available:** ~305 hours

---

## Overview

Building network protocols and concurrency primitives. From thread pools to full TCP implementation, creating the foundational systems programming stack.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), integration testing, and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

---

## Project List

- [ ] **Thread Pool with Work-Stealing** - Custom scheduler with ARM optimization for parallel task execution | 20-25 hours | Mar 1-25, 2026
- [ ] **Lock-Free Data Structures** - Atomics and ARM memory model for concurrent data structures | 25-30 hours | Mar 26 - Apr 24, 2026
- [ ] **DNS Server** - Caching resolver with ad-blocking on Raspberry Pi 5 (uses Bloom Filter from Evolution) | 30-40 hours | Apr 25 - May 24, 2026
- [ ] **UDP from Scratch** - Complete UDP protocol implementation over raw sockets (uses CRC32/Internet Checksum from Evolution) | 40-50 hours | May 25 - Jul 13, 2026
- [ ] **TCP from Scratch** ⭐⭐⭐ Capstone - Complete TCP implementation with congestion control (uses Sliding Window Protocol, Exponential Backoff, CRC32 from Evolution) | 120-150 hours | Aug 1 - Dec 31, 2026

**Total Estimated Time:** ~235-295 hours

---

## Notes

- TCP from Scratch is the largest project in this phase spanning 4 months
- Thread Pool and Lock-Free structures provide concurrency foundation
- DNS Server uses Bloom Filter from Evolution phase for ad-blocking
- UDP prepares for TCP complexity
- All projects include comprehensive unit testing (GoogleTest), integration testing, and header file documentation per Google C++ Style Guide
- All projects build on Genesis & Evolution phase primitives

---

**Back to [README](../README.md)**
