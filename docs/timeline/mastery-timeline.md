# Phase 2: Evolution - Network and Concurrency - Detailed Timeline

**Work Schedule:** 1 hour/day average  
**Total Hours Available:** ~305 hours

---

## Overview

Building network protocols and concurrency primitives. From thread pools to full TCP implementation, creating the foundational systems programming stack.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), integration testing, and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

---

## Project List

- [X] **Thread Pool with Work-Stealing** - Custom scheduler with ARM optimization for parallel task execution | 20-25 hours
- [ ] **Lock-Free Data Structures** - Atomics and ARM memory model for concurrent data structures | 25-30 hours
- [ ] **DNS Server** - Caching resolver with ad-blocking on Raspberry Pi 5 | 30-40 hours
- [ ] **UDP from Scratch** - Complete UDP protocol implementation over raw sockets | 40-50 hours
- [ ] **TCP from Scratch** ⭐⭐⭐ Capstone - Complete TCP implementation with congestion control | 120-150 hours

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

**Links:**
- [Phase 2 Overview](../overview/phase2-overview.md)
- [Back to README](../../README.md)**
