# Project Adam

> "Building systems from first principles"

A 20-month systems engineering roadmap from data structures to ARM hypervisors, with a focus on **networking, distributed systems.**

**Note:** This is a networking and distributed systems-focused project. Algorithms and data structures taught in class won't be covered unless they're used for something I will build.

---

## Current Status

**Progress:** AHEAD

| Metric              | Value                                              |
| ------------------- | -------------------------------------------------- |
| **Current Phase**   | Phase 1b: Evolution - Networking Primitives & Advanced Algorithms |
| **Progress**        | 0/10 items complete                                 |
| **Days Elapsed**    | 0 days (starts Nov 12)                              |
| **Days Remaining**  | 60 days (ends Jan 10)                               |
| **Hours Invested**  | 26h 44m (~26.7 hours)                               |
| **Hours Remaining** | ~36-47 hours (Phase 1b estimate)                    |
| **Next Item**       | Bloom Filter (Phase 1b Kickoff)                    |

**[Overview](docs/overview/phase1-overview.md)** | **[Timeline](docs/timeline/phase1-timeline.md)** | **[Phase 1b Details](docs/timeline/genesis-b-timeline.md)**

---

## Quick Navigation

- [Overview](#overview)
- [Current Status](#current-status)
- [Phase Summaries](#the-journey)
  - [Phase 1: Foundation](docs/overview/phase1-overview.md)
    - [Phase 1 Timeline](docs/timeline/phase1-timeline.md) - Completion tracking
    - [Phase 1a: Genesis](docs/timeline/genesis-a-timeline.md)
    - [Phase 1b: Evolution](docs/timeline/genesis-b-timeline.md)
  - [Phase 2: Evolution - Network and Concurrency](docs/overview/phase2-overview.md) - [Timeline](docs/timeline/mastery-timeline.md)
  - [Phase 3: Perfection - The World](docs/overview/phase3-overview.md) - [Timeline](docs/timeline/transcendence-timeline.md)
- [Project Highlights](#project-highlights)
- [Timeline](#timeline)
- [Repositories](#repositories)
- [Commitment](#commitment)

---

## Overview

Project Adam is my journey through systems programming, starting with the fundamentals and building up to running multiple Linux virtual machines on a Raspberry Pi 5. Each project builds on the previous ones, creating a cohesive path from basic algorithms to low-level hardware virtualization.

**Start Date:** October 24, 2025  
**End Date:** June 2027 (Graduation)  
**Total Projects:** 14-15 (9 personal + 5-6 class projects)  
**Primary Language:** C++  
**Hardware:** Raspberry Pi 5 (16GB RAM)
**Code Standards:** All projects follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with comprehensive unit testing (GoogleTest) and header file documentation. Time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), implementation, testing, and documentation.

### Why C++?

I'm moving to C++ because I want a low-level understanding of the computer. Web development wasn't cutting it anymore—I needed to understand how things actually work at the machine level. C++ forces you to think about memory, hardware, and performance in ways that high-level languages abstract away.

The skills I build here will transfer exponentially to other languages. Once you understand pointers, memory management, concurrency primitives, and hardware interaction, everything else becomes easier. You can't truly understand systems without understanding what's happening close to the metal.

**I got tired of web development. Time to build real systems.**

### Why "Project Adam"?

Like Adam Warlock—this is my evolution to becoming a cracked programmer. From the first data structure to creating entire virtual worlds, every project builds toward mastery.

---

## The Journey

### Phase 1: Foundation (Oct 24, 2025 - Jan 10, 2026)

#### Phase 1a: Genesis - Data Structures and Algorithms (Oct 24 - Dec 31, 2025)

**[Overview](docs/overview/phase1-overview.md)** | **[Timeline](docs/timeline/phase1-timeline.md)** | **[Phase 1a Details](docs/timeline/genesis-a-timeline.md)**

Building essential data structures and algorithms that form the foundation for all networking and systems projects.

Having already completed NeetCode's DSA courses, this phase focuses on **C++ implementation mastery**: correct syntax, robust testing, and manual memory management (pointers, `new`/`delete`). I have taken CSE 332 (Data Structures & Parallelism) at UW, which covered Min Heap, Dijkstra's Algorithm, and other fundamental algorithms. Data structures and algorithms covered in CSE 332 are not included here unless they're directly used in projects I'll build. CSE 422 (Advanced Toolkit for Modern Algorithms) will cover modern algorithmic techniques like sketching algorithms, sampling, and ML algorithms, complementing this low-level systems focus.

**Projects:** Dynamic Array, Singly LinkedList, Doubly LinkedList, Stack, Queue, Hash Table, Trie, LRU Cache, **Red-Black Tree** ⭐ Capstone

**Focus:** C++ implementation mastery with manual memory management and pointer manipulation

**Total Estimated Time:** ~30-35 hours  
**Available Time:** 68 days × 1 hour/day = 68 hours

#### Phase 1b: Evolution - Networking Primitives & Advanced Algorithms (Nov 12, 2025 - Jan 10, 2026)

**[Overview](docs/overview/phase1-overview.md)** | **[Timeline](docs/timeline/phase1-timeline.md)** | **[Phase 1b Details](docs/timeline/genesis-b-timeline.md)**

Network-focused phase that builds primitives and algorithms directly used in Phase 2's networking projects (DNS, UDP, TCP).

**Projects:** Bloom Filter, Ring Buffer, **Radix Tree** ⭐ Capstone, Skip List, Sliding Window Protocol, CRC32/Internet Checksum, Token Bucket, Exponential Backoff, Consistent Hashing, Bellman-Ford

**Focus:** Networking-focused data structures and algorithms for Phase 2

**Total Estimated Time:** ~36-47 hours  
**Available Time:** 60 days × 1 hour/day = 60 hours

**Phase 1 Total:** ~66-82 hours over 127 days

---

### Phase 2: Evolution - Network and Concurrency (Jan 2026 - Dec 2026)

**[Overview](docs/overview/phase2-overview.md)** | **[Timeline](docs/timeline/mastery-timeline.md)**

Building network protocols and concurrency primitives.

**Projects:** Thread Pool with Work-Stealing, Lock-Free Data Structures, DNS Server, UDP from Scratch, **TCP from Scratch** ⭐⭐⭐ Capstone

**Focus:** Concurrency primitives and network protocol implementation

**Total Estimated Time:** ~235-295 hours  
**Available Time:** ~305 days × 1 hour/day = ~305 hours

---

### Phase 3: Perfection - The World (Jan 2027 - June 2027)

**[Overview](docs/overview/phase3-overview.md)** | **[Timeline](docs/timeline/transcendence-timeline.md)**

Distributed systems and virtualization. Like Adam Warlock's perfection—the ultimate creation.

**Projects:** BitTorrent Client, Custom Memory Allocators, **ARM Hypervisor** ⭐⭐⭐⭐⭐ Capstone

**Focus:** Distributed systems and virtualization

**Total Estimated Time:** ~150-190 hours  
**Available Time:** ~181 days × 1 hour/day = ~181 hours

---

### Class Projects (Integrated Throughout)

- Memory-Mapped Files (CSE 451 - Winter 2026)
- Distributed Key-Value Store (CSE 452 - Spring 2026)
- MiniJava Compiler (CSE 401 - Spring 2026)
- Software-Defined Networking (CSE 461 - Fall 2026 or Winter 2027)
- Data Center Systems (CSE 453 - Fall 2026 or Winter 2027)†
- SimpleDB (CSE 444 - if schedule permits)†

†Schedule to be confirmed when courses are announced

---

## Project Highlights

### TCP from Scratch (Aug - Dec 2026)

Complete implementation of TCP protocol including:

- Three-way handshake and connection management
- Sliding window flow control
- Congestion control (Reno, Cubic, BBR)
- Packet reordering and retransmission
- Benchmarks vs kernel stack

### ARM Hypervisor (Apr - June 2027) Capstone

Type-2 hypervisor on Raspberry Pi 5:

- ARM EL2 (Hypervisor mode) implementation
- Stage-2 page tables for memory virtualization
- Device emulation (UART, timer, storage, network)
- Multiple Linux VMs running simultaneously
- Can SSH into virtualized guests

---

## Technology Stack

**Languages:** C++17, ARM Assembly, JavaScript  
**Systems:** Linux, bare-metal ARM  
**Hardware:** Raspberry Pi 5 (16GB, Cortex-A76)
**Tools:** GCC, GDB, Valgrind, Git  
**Concepts:** Concurrency, networking, distributed systems, virtualization

---

## Timeline

**2025**

- Oct 24 - Dec 31: Phase 1a: Genesis (Data Structures and Algorithms)

**2026**

- Jan 10: Phase 1b complete (moved up from Feb 28)

**Phase 1: Foundation (Oct 2025 - Feb 2026)**

- [Overview](docs/overview/phase1-overview.md) | [Timeline](docs/timeline/phase1-timeline.md)
- Mar - Dec: Phase 2: Evolution - Network and Concurrency (DNS, UDP, TCP)
  - [Overview](docs/overview/phase2-overview.md) | [Timeline](docs/timeline/mastery-timeline.md)
  - Aug-Dec: TCP from Scratch (4 months)

**2027**

- Jan - Jun: Phase 3: Perfection - The World (BitTorrent, Hypervisor)
  - [Overview](docs/overview/phase3-overview.md) | [Timeline](docs/timeline/transcendence-timeline.md)
  - Apr-Jun: ARM Hypervisor (Capstone)
- **Graduate June 2027**

---

## Repositories

As projects are completed, repositories will be linked here:

### Personal Projects (9 total)

**Phase 1: Foundation (DS&A)**

1. [ ] DS&A Library (Core Toolkit & Networking Primitives)

**Phase 2: Evolution - Network and Concurrency**

2. [ ] Thread Pool
3. [ ] Lock-Free Structures
4. [ ] DNS Server
5. [ ] UDP from Scratch
6. [ ] TCP from Scratch ⭐⭐⭐

**Phase 3: Perfection - The World**

7. [ ] BitTorrent Client
8. [ ] Custom Allocators
9. [ ] ARM Hypervisor ⭐⭐⭐⭐⭐

### Class Projects (5-6 total)

1. [ ] Memory-Mapped Files (CSE 451)
2. [ ] Distributed KV Store (CSE 452)
3. [ ] MiniJava Compiler (CSE 401)
4. [ ] Software-Defined Networking (CSE 461)
5. [ ] Data Center Systems (CSE 453)†
6. [ ] SimpleDB (CSE 444)†

---

## Goals

**Technical:** Master systems programming from algorithms to hardware, with emphasis on networking  
**Academic:** Apply coursework to real-world projects  
**Professional:** Build portfolio demonstrating complete systems mastery  
**Personal:** Become cracked through deliberate practice and building from scratch

---

## Commitment

**Daily:** 1 hour on personal projects  
**Class Projects:** As needed (separate from daily hour)  
**Total Time Investment:** ~730 hours over 20 months  
**Philosophy:** Quality over quantity—focus on networking-critical implementations

---

## The Path to Mastery

Each phase is a step toward perfection:

1. **Phase 1: Foundation** - Create the foundations (Data Structures & Algorithms & Networking Primitives)
2. **Phase 2: Evolution** - Build network protocols and concurrency primitives (DNS, UDP, TCP)
3. **Phase 3: Perfection** - Make new worlds (Hypervisor, Virtual Machines)

By June 2027, I'll have built everything from scratch—from the first linked list to running multiple operating systems on hardware I control completely.

---

## Resources & Learning

Throughout this journey, I'll be documenting:

- Technical blog posts on key learnings
- Architecture diagrams and design decisions
- Code snippets and debugging stories
- Resources and references that helped

---

**Status:** Phase 1b: Evolution - Networking Primitives & Advanced Algorithms  
**Last Updated:** November 11, 2025  
**Next Milestone:** Phase 1a: Genesis (Data Structures and Algorithms) complete (December 31, 2025)

---

## License

Each project repository will have its own license. Generally using MIT License for educational projects.

## Acknowledgments

- University of Washington Computer Science & Engineering
- CSE 451, 452, 401, 461, 444 course staff
- ARM Architecture Reference Manual
- The systems programming community

---

_From the ground up. Every line of code. Every protocol. Every algorithm. Ascending to perfection._