# Phase 2: Concurrency - Detailed Timeline

**Duration:** Jan 2026 - Apr 2026 (~90 days)
**Work Schedule:** 1 hour/day average
**Total Hours Available:** ~90 hours

---

## Overview

Building concurrency primitives and exploring parallel computing. This phase focuses on thread synchronization, lock-free programming, and ARM-specific memory model optimizations.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), integration testing and benchmarks, and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

---

## Project List

- [X] **Thread Pool with Work-Stealing** - Custom scheduler with ARM optimization for parallel task execution | 20-25 hours | Jan 2026
- [ ] **Lock-Free Data Structures** ⭐⭐ Capstone - Atomics and ARM memory model for concurrent data structures | 25-30 hours | Feb-Apr 2026

**Total Estimated Time:** ~45-55 hours

---

## Detailed Project Breakdown

### Thread Pool with Work-Stealing (Jan 2026) ✓ Completed

**Estimated:** 20-25 hours | **Status:** Complete

- Custom task scheduler with work-stealing algorithm
- Thread-safe task queue implementation
- ARM-specific optimizations
- Benchmarks vs std::async and other implementations
- Comprehensive unit tests

### Lock-Free Data Structures (Feb-Apr 2026) ⭐⭐ Capstone

**Estimated:** 25-30 hours | **Status:** In Progress

**Components:**
1. Lock-free stack using compare-and-swap (CAS)
2. Lock-free queue with hazard pointers
3. Lock-free hash table
4. ABA problem solutions
5. Memory ordering experiments

**Key Learnings:**
- C++ atomics and memory ordering (relaxed, acquire, release, seq_cst)
- ARM memory model specifics
- Performance comparison vs lock-based implementations
- Benchmarking concurrent data structures

---

## Notes

- Lock-Free Data Structures is the capstone project for this phase
- Thread Pool provides foundation for later networking projects
- ARM-specific memory model knowledge is critical for performance
- All projects include comprehensive benchmarks comparing performance
- Skills from this phase enable high-performance networking in Phase 3

---

**Links:**
- [Phase 2 Overview](../overview/phase2-overview.md)
- [Back to README](../../README.md)
