# Phase 1b: Evolution - Networking Primitives & Advanced Algorithms - Detailed Breakdown

**Duration:** Jan 1 - Feb 28, 2026 (59 days)  
**Work Schedule:** 1 hour/day average  
**Total Hours Available:** 59 hours

---

## Overview

**Network-focused phase** that builds primitives and algorithms directly used in Mastery phase's networking projects (DNS, UDP, TCP). This phase prioritizes practical networking knowledge over academic algorithms.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

---

## Project List

- [ ] **Bloom Filter** - Probabilistic data structure for fast membership testing (used by DNS Server for ad-blocking) | 3-4 hours | Jan 1-4, 2026
- [ ] **Ring Buffer (Circular Buffer)** - Fixed-size circular buffer for packet buffering and producer-consumer patterns | 3-4 hours | Jan 5-8, 2026
- [ ] **Skip List** - Probabilistic alternative to balanced trees with simple implementation | 4-5 hours | Jan 9-13, 2026
- [ ] **Sliding Window Protocol** - TCP flow control mechanism for reliable data transmission (used by TCP from Scratch) | 4-5 hours | Jan 14-18, 2026
- [ ] **CRC32 / Internet Checksum** - Packet integrity validation algorithms (used by UDP and TCP) | 2-3 hours | Jan 19-21, 2026
- [ ] **Token Bucket Algorithm** - Rate limiting and traffic shaping for network congestion | 3-4 hours | Jan 22-25, 2026
- [ ] **Exponential Backoff** - TCP retransmission and congestion control algorithm (used by TCP from Scratch) | 2-3 hours | Jan 26-28, 2026
- [ ] **Consistent Hashing** - Distributed hash table for BitTorrent and distributed systems (used by BitTorrent Client) | 4-5 hours | Jan 29 - Feb 2, 2026
- [ ] **Bellman-Ford Algorithm** - Distance-vector routing algorithm (like RIP protocol) | 5-6 hours | Feb 3-9, 2026
- [ ] **Radix Tree (Patricia Trie)** ⭐ Capstone - Compressed trie for IP routing tables and longest prefix match | 6-8 hours | Feb 10-28, 2026

**Total Estimated Time:** ~36-47 hours

---

## Notes

- Radix Tree (Patricia Trie) is the most challenging project in this phase - used for IP routing tables and longest prefix matching
- This phase is intentionally lean and focused—cutting academic algorithms (dynamic programming, advanced graph theory) in favor of networking primitives
- All projects include comprehensive unit testing (GoogleTest) and header file documentation per Google C++ Style Guide
- All projects directly prepare for Phase 2's networking projects (DNS, UDP, TCP)
- Bloom Filter will be used in DNS Server for ad-blocking
- Consistent Hashing will be used in BitTorrent Client for DHT

---

**Links:**
- [Phase 1 Overview](../overview/phase1-overview.md)
- [Phase 1 Timeline](phase1-timeline.md)
- [Back to README](../../README.md)
