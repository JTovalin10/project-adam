# Open Source Contribution Recommendations (C/C++ Focus)

**Status:** Outside the scope of Project Adam
**Purpose:** Curated list of **C/C++ open source projects** for gaining production codebase experience

---

## Overview

This document contains recommendations for **C and C++ open source projects** to contribute to. Contributing to established open source projects provides:

- Experience with large, production codebases
- Collaboration and code review skills
- Understanding of real-world software engineering practices
- Professional networking opportunities
- Resume credibility through public contributions

**Language Focus:** All primary recommendations are **C or C++ codebases** that align with your systems programming skills.

**Important:** Open source contributions are independent from Project Adam's core phases (1-4). They can be pursued:

- During downtime between phases
- After completing Project Adam (post-June 2027)
- Alongside Project Adam as time permits
- During employment for continued learning

---

## C++ Projects (Highest Priority)

### Envoy Proxy ⭐ TOP RECOMMENDATION

**Language:** C++
**Difficulty:** Advanced
**Focus Areas:**

- Layer 7 networking
- Service mesh data plane
- High-performance proxying
- Protocol implementation

**Getting Started:**

- [Envoy Contributor Guide](https://github.com/envoyproxy/envoy/blob/main/CONTRIBUTING.md)
- Read architecture documentation first
- Start with small bug fixes
- Focus on areas related to your TCP knowledge from Phase 3

**Why This is #1:**

- **Pure C++** - Perfect match for your skills
- Powers Istio, AWS App Mesh, and many service meshes
- Directly relevant to Phase 4's CDN project and cloud engineering roles
- High-performance networking focus aligns with your TCP work
- Modern C++ codebase with excellent engineering practices
- Very impressive on resume for cloud roles

---

### gRPC (C++ Core) ⭐ HIGHLY RECOMMENDED

**Language:** C++ core (also has Go, Java, Python bindings)
**Difficulty:** Intermediate-Advanced
**Focus Areas:**

- RPC framework
- Protocol Buffers
- HTTP/2 implementation
- Microservices communication

**Getting Started:**

- [gRPC Contributor Guide](https://grpc.io/community/)
- **Focus on C++ core implementation** (not the bindings)
- Work on examples or documentation first
- Improve performance or add features

**Why Contribute:**

- **C++ core** aligns perfectly with your skills
- Modern RPC standard used everywhere in cloud
- Directly uses HTTP/2 (complements your networking knowledge)
- Wide industry adoption
- Microservices relevance for cloud engineering

---

### Folly (Meta C++) ⭐ PERFECT FOR PHASE 2 SKILLS

**Language:** C++
**Difficulty:** Advanced
**Focus Areas:**

- High-performance C++ components
- **Lock-free data structures**
- Memory allocators
- Concurrency primitives

**Getting Started:**

- [Folly GitHub](https://github.com/facebook/folly)
- Study specific components (start with Future, locks, or containers)
- Improve documentation or add benchmarks
- Contribute tests for edge cases

**Why Contribute:**

- **Production C++ library from Meta**
- **Directly relevant to your Phase 2 lock-free work**
- High-quality codebase with modern C++ (C++17/20)
- Learn advanced C++ techniques from Meta engineers
- Performance-critical code
- Shows you can work at FAANG-level C++

---

## C Projects (High-Performance Systems)

### nginx ⭐ TOP C PROJECT

**Language:** C
**Difficulty:** Advanced
**Focus Areas:**

- Web server implementation
- Reverse proxy
- Load balancing
- High-performance I/O

**Getting Started:**

- [nginx Development Guide](https://nginx.org/en/docs/dev/development_guide.html)
- Study nginx module system
- Start with documentation or bug reports
- Create custom modules

**Why Contribute:**

- **Pure C** - Excellent for C programming skills
- Most popular web server (33% of all websites)
- High-performance networking (event-driven, async I/O)
- **Directly relevant to CDN/caching work** (Phase 4)
- Production system used by millions
- Very impressive on resume

---

### HAProxy

**Language:** C
**Difficulty:** Advanced
**Focus Areas:**

- Load balancing algorithms
- TCP/HTTP proxying
- Health checking
- Connection management

**Getting Started:**

- [HAProxy Contributor Guide](https://github.com/haproxy/haproxy/blob/master/CONTRIBUTING)
- Read architecture documentation
- Focus on configuration improvements first
- Work on new load balancing algorithms

**Why Contribute:**

- **Pure C** codebase
- Industry-standard load balancer
- Directly relevant to cloud infrastructure
- Performance-focused (complements your optimization work)
- Used in production at scale

---

### Redis

**Language:** C
**Difficulty:** Intermediate-Advanced
**Focus Areas:**

- In-memory data structures
- Caching strategies
- Replication and persistence
- Performance optimization

**Getting Started:**

- [Redis Contributor Guide](https://redis.io/community)
- Start with modules or simple bug fixes
- Add features to data structures
- Optimize performance

**Why Contribute:**

- **Pure C** with very readable codebase
- Most popular caching system
- **Relevant to Phase 4's caching work**
- Performance-critical code
- Relatively approachable for beginners
- Large, active community

---

### libuv

**Language:** C
**Difficulty:** Intermediate-Advanced
**Focus Areas:**

- Async I/O
- Event loop implementation
- Cross-platform abstractions
- Performance

**Getting Started:**

- [libuv Contributor Guide](https://github.com/libuv/libuv/blob/v1.x/CONTRIBUTING.md)
- Powers Node.js runtime
- Work on platform-specific improvements (ARM for your Pi 5!)
- Add tests or fix bugs

**Why Contribute:**

- **Pure C** with clean codebase
- Core async I/O library
- Networking relevance (event loops used in all async servers)
- Wide adoption
- Good for learning async programming patterns

---

## C++ Performance & Specialized

### Abseil (Google C++)

**Language:** C++
**Difficulty:** Intermediate-Advanced
**Focus Areas:**

- C++ standard library extensions
- Containers, algorithms, synchronization
- Google's C++ practices

**Getting Started:**

- [Abseil GitHub](https://github.com/abseil/abseil-cpp)
- Study Abseil components
- Contribute tests or documentation
- Improve performance

**Why Contribute:**

- **Pure C++** from Google
- Production library used at Google scale
- Modern C++ best practices
- Complements your C++ knowledge

---

### Seastar (High-Performance C++)

**Language:** C++
**Difficulty:** Advanced
**Focus Areas:**

- High-performance async framework
- Shared-nothing architecture
- Zero-copy networking

**Getting Started:**

- [Seastar GitHub](https://github.com/scylladb/seastar)
- Study the architecture (very advanced)
- Work on examples or documentation
- Requires deep C++ and systems knowledge

**Why Contribute:**

- **Cutting-edge C++** framework
- Extreme performance focus (powers ScyllaDB)
- Async networking patterns
- Very advanced, impressive on resume

---

## Other Languages (Optional - If You Want to Learn)

### Go Projects

**Kubernetes**
**Language:** Go
**Difficulty:** Advanced
**Why Consider:** Most important cloud platform

- [Contributor Guide](https://kubernetes.io/docs/contribute/)
- Extremely valuable for cloud engineering careers
- Would require learning Go

**Prometheus**
**Language:** Go
**Difficulty:** Intermediate
**Why Consider:** Industry standard for metrics/observability

- [Contributor Guide](https://prometheus.io/community/)
- Good for observability experience

**etcd**
**Language:** Go
**Difficulty:** Advanced
**Why Consider:** Relates to CSE 452 (distributed KV store, Raft consensus)

- [Contributor Guide](https://github.com/etcd-io/etcd/blob/main/CONTRIBUTING.md)
- Interesting for distributed systems theory

---

### Rust Projects

**Tokio**
**Language:** Rust
**Difficulty:** Intermediate-Advanced
**Why Consider:** Industry-leading async runtime

- [Contributor Guide](https://github.com/tokio-rs/tokio/blob/master/CONTRIBUTING.md)
- Powers many Rust networking applications
- Async I/O similar to libuv
- Growing adoption in cloud infrastructure

**Firecracker**
**Language:** Rust
**Difficulty:** Advanced
**Why Consider:** AWS's microVM technology

- [GitHub](https://github.com/firecracker-microvm/firecracker)
- Powers AWS Lambda and Fargate
- Virtualization and security focus
- Very impressive on resume for cloud roles

**TiKV**
**Language:** Rust
**Difficulty:** Advanced
**Why Consider:** Distributed transactional key-value database

- [Contributor Guide](https://github.com/tikv/tikv/blob/master/CONTRIBUTING.md)
- Cloud-native, CNCF project
- Raft consensus implementation
- Relates to CSE 452 concepts

**Servo**
**Language:** Rust
**Difficulty:** Advanced
**Why Consider:** Modern browser engine (Mozilla)

- [GitHub](https://github.com/servo/servo)
- Parallel rendering, cutting-edge web technologies
- Good for learning Rust's memory safety features

---

### Java Projects

**Apache Kafka**
**Language:** Java (Scala)
**Difficulty:** Advanced
**Why Consider:** Industry-standard distributed streaming platform

- [Contributor Guide](https://kafka.apache.org/contributing)
- Used everywhere in cloud/data infrastructure
- Distributed systems, messaging patterns
- Very valuable for cloud engineering roles

**Netty**
**Language:** Java
**Difficulty:** Intermediate-Advanced
**Why Consider:** High-performance networking framework

- [Contributor Guide](https://netty.io/community.html)
- Powers many distributed systems (Cassandra, Elasticsearch, gRPC Java)
- Async networking similar to your C++ work
- Good for understanding JVM networking

**Apache Cassandra**
**Language:** Java
**Difficulty:** Advanced
**Why Consider:** Distributed NoSQL database

- [Contributor Guide](https://cassandra.apache.org/doc/latest/development/index.html)
- Large-scale distributed systems
- Similar concepts to CSE 452
- Used at FAANG scale

**Lucene / Elasticsearch**
**Language:** Java
**Difficulty:** Intermediate-Advanced
**Why Consider:** Search engine library/distributed search

- [Lucene](https://lucene.apache.org/core/), [Elasticsearch](https://github.com/elastic/elasticsearch)
- Distributed search and analytics
- Performance-critical indexing algorithms
- Wide industry adoption

---

## Recommended Prioritization (C/C++ Only)

### For Cloud Engineering Roles - Pick 2-3 Maximum

**Tier 1 - Start Here (Pick 1):**

1. **Envoy Proxy** (C++) ⭐⭐⭐ - Service mesh, most relevant to cloud roles
2. **nginx** (C) ⭐⭐⭐ - Web server/proxy, production critical
3. **gRPC** (C++ core) ⭐⭐⭐ - Modern RPC, microservices

**Tier 2 - Add One More (Optional):** 4. **Folly** (C++) - Advanced C++, Meta engineering 5. **Redis** (C) - Caching, easier entry point 6. **HAProxy** (C) - Load balancing

**Tier 3 - Specialization:** 7. **libuv** (C) - Async I/O fundamentals 8. **Abseil** (C++) - Google C++ practices 9. **Seastar** (C++) - Advanced, cutting-edge

## Links

- [Back to README](../README.md)
- [Books & Resources](books-and-resources.md)
- [Phase 5: Beyond](overview/phase5-overview.md)
