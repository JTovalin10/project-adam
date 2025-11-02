# Project Adam

> "Building systems from first principles"

A 20-month systems engineering roadmap from data structures to ARM hypervisors.

## Overview

Project Adam is my journey through systems programming, starting with the fundamentals and building up to running multiple Linux virtual machines on a Raspberry Pi 5. Each project builds on the previous ones, creating a cohesive path from basic algorithms to low-level hardware virtualization.

**Start Date:** October 24, 2025  
**End Date:** June 2027 (Graduation)  
**Total Projects:** 16-17 (11 personal + 5-6 class projects)  
**Primary Language:** C++  
**Hardware:** Raspberry Pi 5 (8GB RAM), MacBook

## Why C++?

I'm moving to C++ because I want a low-level understanding of the computer. Web development wasn't cutting it anymore—I needed to understand how things actually work at the machine level. C++ forces you to think about memory, hardware, and performance in ways that high-level languages abstract away.

The skills I build here will transfer exponentially to other languages. Once you understand pointers, memory management, concurrency primitives, and hardware interaction, everything else becomes easier. You can't truly understand systems without understanding what's happening close to the metal.

**I got tired of web development. Time to build real systems.**

## Why "Project Adam"?

Like Adam Warlock or Adam from Records of Ragnarok—the perfect human, created to rival the gods.

**This is my journey to become cracked.** To build coding skills that reach that level. Starting from nothing and ascending to mastery through deliberate practice and building everything from scratch.

From the first data structure to creating entire virtual worlds. Every line of code bringing me closer to that perfection.

## The Journey

### Phase 1: The Core Toolkit (Oct - Dec 2025)

Building the essential, high-value data structures and algorithms. This is the foundation that nearly all other projects will depend on.

Having already completed NeetCode's DSA courses, the primary goal of this phase isn't to *learn* these concepts from scratch. Instead, it's to master their **C++ implementation**, focusing on correct syntax, robust testing, and manual memory management (pointers, `new`/`delete`). This is why the algorithm list is intentionally focused on core tools rather than exhaustive coverage.

  - [x] Dynamic Array (Vector)
  - [x] Singly Linked List
  - [ ] Doubly Linked List
  - [ ] Stack (implemented with Vector)
  - [ ] Queue (implemented with List)
  - [ ] Hash Table (Separate Chaining)
  - [ ] Priority Queue (Binary Heap)
  - [ ] Binary Search Tree
  - [ ] LRU Cache (using Hash Table + Doubly Linked List)
  - [ ] Quick Sort
  - [ ] Merge Sort
  - [ ] Binary Search
  - [ ] Dijkstra's Algorithm

### Phase 2: Advanced Algorithms & Systems Primitives (Jan - Feb 2026)

Mastering the implementation of more complex algorithms and data structures that are foundational for databases, networking, and high-performance systems.

**Advanced Data Structures:**

  - [ ] Red-Black Tree
  - [ ] B-Tree
  - [ ] Trie (Prefix Tree)
  - [ ] Bloom Filter
  - [ ] Consistent Hashing Ring

**Core Graph Algorithms:**

  - [ ] Bellman-Ford Algorithm
  - [ ] Kruskal's OR Prim's Algorithm (MST)
  - [ ] Topological Sort
  - [ ] Tarjan's Algorithm (Strongly Connected Components)

**String & Pattern Matching:**

  - [ ] Rabin-Karp Algorithm
  - [ ] KMP Pattern Matching

**Dynamic Programming:**

  - [ ] Longest Common Subsequence
  - [ ] 0/1 Knapsack

**Network Flow:**

  - [ ] Edmonds-Karp Algorithm (Max Flow)

### Phase 3: The Stack (Mar 2026 - Dec 2026)

From concurrency to networking protocols.

  - **Thread Pool with Work-Stealing** - Custom scheduler with ARM optimization
  - **Lock-Free Data Structures** - Atomics and ARM memory model
  - **DNS Server** - Caching resolver with ad-blocking on Pi 5
  - **UDP from Scratch** - Protocol implementation over raw sockets
  - **TCP from Scratch** ⭐⭐⭐ - Complete TCP with congestion control (4 months)

### Phase 4: The World (Jan 2027 - June 2027)

Distributed systems and virtualization.

  - **BitTorrent Client** - P2P file-sharing with DHT
  - **Custom Memory Allocators** - Buddy, slab, and pool allocators
  - **ARM Hypervisor on Raspberry Pi 5** ⭐⭐⭐⭐⭐ - Type-2 hypervisor running multiple Linux VMs (CAPSTONE)

### Class Projects (Integrated Throughout)

  - Memory-Mapped Files (CSE 451 - Winter 2026)
  - Distributed Key-Value Store (CSE 452 - Spring 2026)
  - MiniJava Compiler (CSE 401 - Spring 2026)
  - Software-Defined Networking (CSE 461 - Fall 2026 or Winter 2027)
  - Data Center Systems (CSE 453 - Fall 2026 or Winter 2027)†
  - SimpleDB (CSE 444 - if schedule permits)†

†Schedule to be confirmed when courses are announced

## Project Highlights

### TCP from Scratch (Aug - Dec 2026)

Complete implementation of TCP protocol including:

  - Three-way handshake and connection management
  - Sliding window flow control
  - Congestion control (Reno, Cubic, BBR)
  - Packet reordering and retransmission
  - Benchmarks vs kernel stack

### ARM Hypervisor (Apr - June 2027) 🏆 CAPSTONE

Type-2 hypervisor on Raspberry Pi 5:

  - ARM EL2 (Hypervisor mode) implementation
  - Stage-2 page tables for memory virtualization
  - Device emulation (UART, timer, storage, network)
  - Multiple Linux VMs running simultaneously
  - Can SSH into virtualized guests

**Creating new worlds on a $80 computer.**

## Technology Stack

**Languages:** C++17, ARM Assembly, JavaScript  
**Systems:** Linux, bare-metal ARM  
**Hardware:** Raspberry Pi 5 (8GB, Cortex-A76), MacBook  
**Tools:** GCC, CMake, GDB, Git  
**Concepts:** Concurrency, networking, distributed systems, virtualization

## Timeline

```
2025 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
     Oct      Nov      Dec               ┃
     [──── Phase 1: Core Toolkit ───]    ┃
                                          ┃
2026 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
     [Ph 2: Adv Alg][─ Phase 3: The Stack ─]
     [Jan-Feb]    [Mar ─────────── Dec]   ┃
     [...TCP 4 months... ]               ┃
                                          ┃
2027 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
     [──── Phase 4: The World ─────]     ┃
     [Jan ────────── Jun]                ┃
     [── HYPERVISOR CAPSTONE ──]         ┃
                                          ┃
     Graduate June 2027 🎓                ┃
```

## Current Status

**Current Project:** Phase 1: The Core Toolkit  
**Progress:** 2/13 items complete  
**Next Up:** Doubly Linked List

## Repositories

As projects are completed, repositories will be linked here:

### Personal Projects (11)

**Phase 1 & 2: Algorithms**

1.  [ ] DS\&A Library (Core Toolkit & Advanced Primitives)

**Phase 3: The Stack**
2\. [ ] Thread Pool
3\. [ ] Lock-Free Structures
4\. [ ] DNS Server
5\. [ ] UDP from Scratch
6\. [ ] TCP from Scratch ⭐⭐⭐

**Phase 4: The World**
7\. [ ] BitTorrent Client
8\. [ ] Custom Allocators
9\. [ ] ARM Hypervisor ⭐⭐⭐⭐⭐

*(Note: Original list item count was 11, merging DS\&A into one repo and removing 'Visualization' matches this.)*

### Class Projects (5-6)

1.  [ ] Memory-Mapped Files (CSE 451)
2.  [ ] Distributed KV Store (CSE 452)
3.  [ ] MiniJava Compiler (CSE 401)
4.  [ ] Software-Defined Networking (CSE 461)
5.  [ ] Data Center Systems (CSE 453)†
6.  [ ] SimpleDB (CSE 444)†

## Goals

**Technical:** Master systems programming from algorithms to hardware  
**Academic:** Apply coursework to real-world projects  
**Professional:** Build portfolio demonstrating complete systems mastery  
**Personal:** Become cracked through deliberate practice and building from scratch

## Commitment

**Daily:** 1 hour on personal projects  
**Class Projects:** As needed (separate from daily hour)  
**Total Time Investment:** \~730 hours over 20 months  
**Philosophy:** Consistent daily progress compounds into mastery

## The Path to Mastery

Like Adam ascending to rival the gods, each project is a step toward perfection:

1.  **Genesis** - Create the foundations (Core Toolkit)
2.  **Growth** - Develop understanding (Advanced Algorithms, Concurrency)
3.  **Connection** - Build networks (Protocols, Distributed Systems)
4.  **Creation** - Make new worlds (Hypervisor, Virtual Machines)

By June 2027, I'll have built everything from scratch—from the first linked list to running multiple operating systems on hardware I control completely.

## Resources & Learning

Throughout this journey, I'll be documenting:

  - Technical blog posts on key learnings
  - Architecture diagrams and design decisions
  - Code snippets and debugging stories
  - Resources and references that helped

-----

**Status:** 🌱 Genesis Phase (Phase 1)  
**Last Updated:** November 2, 2025  
**Next Milestone:** Phase 1: Core Toolkit complete (December 31, 2025)

-----

## License

Each project repository will have its own license. Generally using MIT License for educational projects.

## Acknowledgments

  - University of Washington Computer Science & Engineering
  - CSE 451, 452, 401, 461, 444 course staff
  - ARM Architecture Reference Manual
  - The systems programming community

-----

*From the ground up. Every line of code. Every protocol. Every algorithm. Ascending to perfection.*