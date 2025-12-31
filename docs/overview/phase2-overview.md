# Phase 2: Concurrency - Overview

**Duration:** Jan 2026 - Apr 2026 (~90 days)
**Work Schedule:** 1 hour/day average
**Total Hours Available:** ~90 hours

---

## Overview

Building concurrency primitives and exploring parallel computing. This phase focuses on thread synchronization, lock-free programming, and ARM-specific memory model optimizations. Production code uses industry-standard libraries (STL, Boost, Folly, `absl`, etc.); Phase 1 data structures remain educational references only.

This phase establishes the concurrency foundation needed for high-performance networking in Phase 3 and the distributed systems capstone in Phase 4.

---

## Code Standards

All time estimates include:
- Project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`)
- Comprehensive unit testing (GoogleTest)
- Integration testing and benchmarks
- Header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

---

## Projects

**Concurrency Primitives:**
- **Thread Pool with Work-Stealing** (20-25 hours)
  - Custom scheduler with ARM optimization
  - Work-stealing algorithm for load balancing
  - Benchmarks vs std::async and other thread pool implementations

- **Lock-Free Data Structures** ⭐⭐ Capstone (25-30 hours)
  - Atomics and ARM memory model
  - Lock-free stack, queue, and hash table
  - Memory ordering and ABA problem solutions
  - Performance comparison vs lock-based implementations

**Total Estimated Time:** ~45-55 hours
**Available Time:** ~90 days × 1 hour/day = ~90 hours

---

## Key Learning Outcomes

- Understanding of C++ atomics and memory ordering
- ARM memory model specifics (TSO vs weak ordering)
- Lock-free algorithm design patterns
- Performance implications of synchronization primitives
- Work-stealing scheduler implementation

---

## Links

- [Phase 2 Timeline](../timeline/phase2-timeline.md)
- [Back to README](../../README.md)

