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

### Phase 1: The Foundation (Oct 2025 - Feb 2026)
Building the algorithmic and data structure foundation.

- **Data Structures & Algorithms Library** - Comprehensive C++ implementation
- **Advanced Algorithms Library** - Max flow, string algorithms, computational geometry
- **Algorithm Visualization** - Web platform for algorithm demos

### Phase 2: The Stack (Mar 2026 - Dec 2026)
From concurrency to networking protocols.

- **Thread Pool with Work-Stealing** - Custom scheduler with ARM optimization
- **Lock-Free Data Structures** - Atomics and ARM memory model
- **DNS Server** - Caching resolver with ad-blocking on Pi 5
- **UDP from Scratch** - Protocol implementation over raw sockets
- **TCP from Scratch** ⭐⭐⭐ - Complete TCP with congestion control (4 months)

### Phase 3: The World (Jan 2027 - June 2027)
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
     Oct        Nov        Dec           ┃
     [────── DS&A Library ──────]        ┃
                                          ┃
2026 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
     [Adv Alg][Viz][Thread][Lock-Free]   ┃
     [DNS][UDP][──── TCP 4 months ────]  ┃
                                          ┃
2027 ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
     [BitTorrent][Allocators]            ┃
     [──── HYPERVISOR CAPSTONE ────]     ┃
                                          ┃
     Graduate June 2027 🎓                ┃
```

## Current Status

**Current Project:** Data Structures & Algorithms Library  
**Progress:** 0/16 projects complete  
**Next Up:** Advanced Algorithms Library (January 2026)  

## Repositories

As projects are completed, repositories will be linked here:

### Personal Projects (11)
1. [ ] DS&A Library
2. [ ] Advanced Algorithms
3. [ ] Algorithm Visualization
4. [ ] Thread Pool
5. [ ] Lock-Free Structures
6. [ ] DNS Server
7. [ ] UDP from Scratch
8. [ ] TCP from Scratch ⭐⭐⭐
9. [ ] BitTorrent Client
10. [ ] Custom Allocators
11. [ ] ARM Hypervisor ⭐⭐⭐⭐⭐

### Class Projects (5-6)
1. [ ] Memory-Mapped Files (CSE 451)
2. [ ] Distributed KV Store (CSE 452)
3. [ ] MiniJava Compiler (CSE 401)
4. [ ] Software-Defined Networking (CSE 461)
5. [ ] Data Center Systems (CSE 453)†
6. [ ] SimpleDB (CSE 444)†

## Goals

**Technical:** Master systems programming from algorithms to hardware  
**Academic:** Apply coursework to real-world projects  
**Professional:** Build portfolio demonstrating complete systems mastery  
**Personal:** Become cracked through deliberate practice and building from scratch  

## Commitment

**Daily:** 1 hour on personal projects  
**Class Projects:** As needed (separate from daily hour)  
**Total Time Investment:** ~730 hours over 20 months  
**Philosophy:** Consistent daily progress compounds into mastery  

## The Path to Mastery

Like Adam ascending to rival the gods, each project is a step toward perfection:

1. **Genesis** - Create the foundations (data structures)
2. **Growth** - Develop understanding (algorithms, concurrency)
3. **Connection** - Build networks (protocols, distributed systems)
4. **Creation** - Make new worlds (hypervisor, virtual machines)

By June 2027, I'll have built everything from scratch—from the first linked list to running multiple operating systems on hardware I control completely.

## Resources & Learning

Throughout this journey, I'll be documenting:
- Technical blog posts on key learnings
- Architecture diagrams and design decisions
- Code snippets and debugging stories
- Resources and references that helped

---

**Status:** 🌱 Genesis Phase  
**Last Updated:** October 24, 2025  
**Next Milestone:** DS&A Library complete (December 31, 2025)

---

## License

Each project repository will have its own license. Generally using MIT License for educational projects.

## Acknowledgments

- University of Washington Computer Science & Engineering
- CSE 451, 452, 401, 461, 444 course staff
- ARM Architecture Reference Manual
- The systems programming community

---

*From the ground up. Every line of code. Every protocol. Every algorithm. Ascending to perfection.*
