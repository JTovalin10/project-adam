# Phase 2: Evolution - Network and Concurrency - Overview

**Duration:** Mar 2026 - Dec 2026 (10 months, ~305 days)  
**Work Schedule:** 1 hour/day average  
**Total Hours Available:** ~305 hours

---

## Overview

Building network protocols and concurrency primitives. From thread pools to full TCP implementation, creating the foundational systems programming stack. All production code here uses industry-standard libraries (STL, Boost, Folly, `absl`, etc.); the hand-written data structures from Phase 1 are retained only as learning references.

---

## Code Standards

All time estimates include:
- Project setup (`.h`, `.cpp`, `gtest.cpp`, `makefile`)
- Comprehensive unit testing (GoogleTest)
- Integration testing
- Header file documentation following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

---

## Projects

**Concurrency Primitives:**
- Thread Pool with Work-Stealing (20-25 hours)
- Lock-Free Data Structures (25-30 hours)

**Network Protocols:**
- DNS Server (30-40 hours)
- UDP from Scratch (40-50 hours)
- **TCP from Scratch** ⭐⭐⭐ Capstone (120-150 hours)

**Total Estimated Time:** ~235-295 hours  
**Available Time:** ~305 days × 1 hour/day = ~305 hours

---

## Key Milestones

- **Mar:** Thread Pool foundation
- **Apr:** Lock-Free structures
- **May-Jun:** DNS Server
- **Jun-Jul:** UDP protocol
- **Aug-Dec:** TCP protocol (4 months)

---

## Links

- [Phase 2 Timeline](../timeline/mastery-timeline.md)
- [Back to README](../../README.md)

