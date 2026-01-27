# Project Adam

> "Building systems from first principles"

A 9-month systems engineering roadmap from data structures to distributed systems, with a focus on **concurrency, networking, and distributed systems.**

---

## Current Status

**Progress:** ON HOLD

| Metric             | Value                                  |
| ------------------ | -------------------------------------- |
| **Current Phase**  | Phase 3: Networking                    |
| **Status**         | On hold while taking CSE 461           |
| **Hours Invested** | 46h 50m                                |
| **Current Item**   | Staying sharp with getcracked.io       |

> **Note:** Phase 3 is temporarily paused while I take CSE 461 (Computer Networks). Learning the networking material in class before implementing networking projects from scratch. In the meantime, I'm working through [getcracked.io](https://getcracked.io) coding problems to stay sharp and continue learning.

**[Overview](docs/overview/phase3-overview.md)** | **[Timeline](docs/timeline/phase3-timeline.md)**

---

## Quick Navigation

**Phases:**
- [Phase 1: The Basics](docs/overview/phase1-overview.md) - [Timeline](docs/timeline/phase1-timeline.md)
- [Phase 2: Concurrency](docs/overview/phase2-overview.md) - [Timeline](docs/timeline/phase2-timeline.md)
- [Phase 3: Networking](docs/overview/phase3-overview.md) - [Timeline](docs/timeline/phase3-timeline.md)
- [Phase 4: Beyond (Optional)](docs/overview/phase4-overview.md)

**Resources:**
- [Open Source Recommendations](docs/open-source-recommendations.md)
- [Books & Resources](docs/books-and-resources.md)

---

## Overview

Project Adam is a comprehensive journey through systems programming, progressing from fundamental data structures to sophisticated distributed systems. Each project builds on previous work, creating a cohesive path from basic algorithms to production-grade networking and distributed systems.

**Duration:** October 24, 2025 - June 2027
**Core Projects (Phases 1-3):** 6 projects
**Optional Projects (Phase 4):** 6 additional projects
**Primary Languages:** C++ (Phases 1-2), C (Phase 3)
**Hardware:** Raspberry Pi 5 (16GB RAM)

> **Note:** Phase 1 implementations are educational artifacts only. Production code in later phases uses industry-standard libraries (STL, Boost, Folly, `absl`, etc.).

### Why C++?

C++ provides the low-level control necessary for deep systems understanding. Unlike high-level languages that abstract away hardware details, C++ requires explicit management of memory, hardware resources, and performance optimization.

The skills developed through C++ systems programming transfer broadly to other languages and domains. Understanding pointers, memory management, concurrency primitives, and hardware interaction creates a foundation that makes higher-level abstractions more intuitive.

---

## The Journey

### Phase 1: The Basics (Oct 2025 - Jan 2026)
**[Overview](docs/overview/phase1-overview.md)** | **[Timeline](docs/timeline/phase1-timeline.md)**

Building essential data structures and algorithms. C++ implementation mastery with manual memory management.

**Projects:** Dynamic Array, LinkedLists, Stack, Queue, Hash Table, Trie, LRU Cache, Red-Black Tree, Bloom Filter, Ring Buffer, Skip List, Sliding Window Protocol

**Time:** ~68-85 hours

---

### Phase 2: Concurrency (Jan 2026 - Apr 2026)
**[Overview](docs/overview/phase2-overview.md)** | **[Timeline](docs/timeline/phase2-timeline.md)**

Building concurrency primitives and exploring parallel computing.

**Projects:**
- Thread Pool with Work-Stealing
- **Lock-Free Data Structures** ⭐⭐ Capstone

**Time:** ~45-55 hours

---

### Phase 3: Networking (May 2026 - Dec 2026)
**[Overview](docs/overview/phase3-overview.md)** | **[Timeline](docs/timeline/phase3-timeline.md)**

Building network protocols from scratch using C to master POSIX networking APIs. This foundational knowledge will be essential when working with C++ libraries like Boost.Asio.

**Projects:**
- DNS Server
- UDP from Scratch
- **TCP** ⭐⭐⭐ Capstone (using [Level-IP](https://github.com/saminiir/level-ip) to focus on learning)

**Language:** C (POSIX API focus)
**Time:** ~190-240 hours

---

### Phase 4: Beyond (Post-Graduation - Optional)
**[Overview](docs/overview/phase4-overview.md)**

Optional advanced projects for continued learning after mastering the core roadmap.

**Projects:** BitTorrent Client, Custom Memory Allocators, HTTP/2 Server, gRPC Server, Service Mesh Data Plane, QUIC Protocol

**Recommendation:** Prioritize open source contributions over solo projects for maximum career impact.

---

## Technology Stack

**Languages:** C++17 (Phases 1-2), C (Phase 3), ARM Assembly
**Systems:** Linux, bare-metal ARM
**Hardware:** Raspberry Pi 5 (16GB, Cortex-A76)
**Tools:** GCC, GDB, Valgrind, Git
**Standards:** [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) for C++ projects, GoogleTest

---

## Timeline Summary

**2025-2026**
- Oct 2025 - Jan 2026: Phase 1 (The Basics)
- Jan 2026 - Apr 2026: Phase 2 (Concurrency)
- May 2026 - Dec 2026: Phase 3 (Networking)

**2027**
- Jan - Jun: Open Source Contributions / Class Projects
- **Graduate June 2027** - Project Adam Complete
- Jun+: Phase 4 (Optional)

---

## Repositories

### Core Projects (Phases 1-3)

**Phase 1:**
1. [x] DS&A Reference Implementations

**Phase 2:**
2. [x] Thread Pool with Work-Stealing
3. [x] Lock-Free Data Structures ⭐⭐

**Phase 3:**
4. [ ] DNS Server
5. [ ] UDP from Scratch
6. [ ] TCP from Scratch ⭐⭐⭐

### Optional Projects (Phase 4)

7. [ ] BitTorrent Client
8. [ ] Custom Memory Allocators
9. [ ] HTTP/2 Server
10. [ ] gRPC Server
11. [ ] Service Mesh Data Plane
12. [ ] QUIC Protocol

### Outside Project Adam Scope

- [ ] Open Source Contributions - See [recommendations](docs/open-source-recommendations.md)

### Class Projects

1. [ ] Memory-Mapped Files (CSE 451)
2. [ ] Distributed KV Store (CSE 452)
3. [ ] MiniJava Compiler (CSE 401)
4. [ ] Software-Defined Networking (CSE 461)
5. [ ] Data Center Systems (CSE 453)
6. [ ] SimpleDB (CSE 444)

---

## Resources

- **[Open Source Recommendations](docs/open-source-recommendations.md)** - C/C++, Rust, Go, and Java projects to contribute to
- **[Books & Resources](docs/books-and-resources.md)** - Reading progress and learning resources

---

## Goals

**Technical:** Master systems programming from algorithms to hardware
**Academic:** Apply coursework to real-world projects
**Professional:** Build portfolio demonstrating complete systems mastery
**Personal:** Achieve technical excellence through deliberate practice

---

## Commitment

**Daily:** 1 hour on personal projects
**Class Projects:** As needed (separate from daily hour)
**Total Time Investment:** ~730 hours over 20 months
**Philosophy:** Quality over quantity

---

**Status:** Phase 3: Networking (On Hold - CSE 461)
**Last Updated:** January 26, 2026
**Next Milestone:** Complete CSE 461, then DNS Server

---
