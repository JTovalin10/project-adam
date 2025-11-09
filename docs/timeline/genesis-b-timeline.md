# Phase 1b: Evolution - Networking Primitives & Advanced Algorithms - Detailed Breakdown
**Duration:** Dec 1, 2025 - Feb 28, 2026 (90 days)  
**Work Schedule:** 1 hour/day average  
**Total Hours Available:** 90 hours
---
## Overview
**Network-focused phase** that builds primitives and algorithms directly used in Phase 2's networking projects (DNS, UDP, TCP). This phase prioritizes practical networking knowledge over academic algorithms.
**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
---
## Project List
- [ ] **Bloom Filter** - Probabilistic data structure for fast membership testing (used by DNS Server for ad-blocking) | 3-4 hours | Dec 1-4, 2025
- [ ] **Ring Buffer (Circular Buffer)** - Fixed-size circular buffer for packet buffering and producer-consumer patterns | 3-4 hours | Dec 5-8, 2025
- [ ] **Skip List** - Probabilistic alternative to balanced trees with simple implementation | 4-5 hours | Dec 9-13, 2025
- [ ] **CRC32 / Internet Checksum** - Packet integrity validation algorithms (used by UDP and TCP) | 2-3 hours | Dec 14-16, 2025
- [ ] **Token Bucket Algorithm** - Rate limiting and traffic shaping for network congestion | 3-4 hours | Dec 17-20, 2025
- [ ] **Leaky Bucket Algorithm** - Traffic shaping algorithm that smooths bursty traffic (complements Token Bucket) | 3-4 hours | Dec 21-24, 2025
- [ ] **Exponential Backoff** - TCP retransmission and congestion control algorithm (used by TCP from Scratch) | 2-3 hours | Dec 26-28, 2025
- [ ] **A* Algorithm** - Pathfinding algorithm for network routing and topology optimization | 4-5 hours | Dec 29, 2025 - Jan 2, 2026
- [ ] **Bellman-Ford Algorithm** - Distance-vector routing algorithm (like RIP protocol) | 5-6 hours | Jan 3-8, 2026
- [ ] **Sliding Window Protocol** ⭐ Capstone - TCP flow control mechanism for reliable data transmission (Go-Back-N and Selective Repeat variants) | 8-10 hours | Jan 9-28, 2026
**Total Estimated Time:** ~38-50 hours
---
## Notes
- Sliding Window Protocol is the capstone project - implementing both Go-Back-N and Selective Repeat variants, which are fundamental to understanding TCP flow control
- This phase is intentionally lean and focused—cutting academic algorithms in favor of networking primitives directly used in Phase 2
- All projects include comprehensive unit testing (GoogleTest) and header file documentation per Google C++ Style Guide
- All projects directly prepare for Phase 2's networking projects (DNS, UDP, TCP)
- Bloom Filter will be used in DNS Server for ad-blocking
- Token Bucket + Leaky Bucket provide complete understanding of rate limiting and traffic shaping
- Skipping Consistent Hashing (covered in CSE 422 HW1) and Radix Tree (not essential for Phase 2 networking projects)
---
**Links:**
- [Phase 1 Overview](../overview/phase1-overview.md)
- [Phase 1 Timeline](phase1-timeline.md)
- [Back to README](../../README.md)