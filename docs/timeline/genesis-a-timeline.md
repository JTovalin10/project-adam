# Phase 1a: Genesis - Data Structures and Algorithms - Detailed Breakdown
**Duration:** Oct 24 - Dec 31, 2025 (68 days)  
**Work Schedule:** 1 hour/day average  
**Total Hours Available:** 68 hours
---
## Overview
Building essential data structures and algorithms that form the foundation for all networking and systems projects. This phase focuses on **C++ implementation mastery**: correct syntax, robust testing, and manual memory management (pointers, `new`/`delete`). I have taken CSE 332 (Data Structures & Parallelism) at UW, which covered Min Heap, Dijkstra's Algorithm, and other fundamental algorithms. Data structures and algorithms covered in CSE 332 are not included here unless they're directly used in projects I'll build.

**Note:** All time estimates include project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`), comprehensive unit testing (GoogleTest), and header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
---
## Project List
- [x] **Dynamic Array (Vector)** - Dynamic resizing array with amortized O(1) operations | 2 hours | Oct 24-25, 2025
- [x] **Singly LinkedList** - Linear data structure with forward iteration | 2 hours | Oct 26-27, 2025
- [x] **Doubly LinkedList** - Bidirectional linked list for efficient insertions/deletions | 3 hours | Oct 28-30, 2025
- [x] **Stack** - LIFO structure implemented with Doubly LinkedList | 2 hours | Oct 31 - Nov 1, 2025
- [x] **Queue** - FIFO structure implemented with Doubly LinkedList | 2-3 hours | Nov 2-4, 2025
- [x] **Hash Table (Separate Chaining)** - Key-value storage with collision resolution | 4-5 hours | Nov 5-9, 2025
- [x] **Trie (Prefix Tree)** - Tree structure for prefix matching and multi-child node management | 3-4 hours | Nov 10-13, 2025
- [X] **LRU Cache** - Least Recently Used cache with O(1) operations (uses Hash Table + Doubly LinkedList) | 3-4 hours | Nov 14-17, 2025
- [x] **Red-Black Tree** ⭐ Capstone - Self-balancing binary search tree | 12-15 hours | Nov 18 - Dec 2, 2025

**Total Estimated Time:** ~30-35 hours
---
## Notes
- Skipping basic sorting/searching algorithms (Quick Sort, Merge Sort, Binary Search) as these are already mastered from NeetCode
- Skipping Min Heap, Dijkstra's, and Union-Find - Min Heap and Dijkstra's were covered in CSE 332, and Union-Find doesn't provide additional C++ memory management practice beyond what's already learned
- CSE 422 (Advanced Toolkit for Modern Algorithms) will cover modern algorithmic techniques like sketching algorithms, sampling, and ML algorithms - complementing this low-level systems focus
- Thread-safe versions of these data structures will be implemented later for networking projects in Phase 2
- Red-Black Tree is the most challenging project in this phase - self-balancing requires careful rotation logic and parent pointer management
- All projects include comprehensive unit testing (GoogleTest), memory leak checking, and header file documentation per Google C++ Style Guide
- Each project builds understanding for networking and systems programming, with focus on manual memory management and pointer manipulation
---
**Links:**
- [Phase 1 Overview](../overview/phase1-overview.md)
- [Phase 1 Timeline](phase1-timeline.md)
- [Back to README](../../README.md)