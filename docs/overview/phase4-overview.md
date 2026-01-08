# Phase 4: Beyond - Optional Projects

**Timeline:** Post-graduation (June 2027+) or during free time
**Work Schedule:** As time permits
**Purpose:** Advanced projects for continued learning after mastering the core roadmap

---

## Overview

Phase 5 contains optional advanced projects that build upon the skills from Phases 1-4. These projects are not required for the core learning path but provide additional depth in specific areas. They can be completed after graduation, during breaks, or whenever you want to explore a particular topic more deeply.

**Key Principle:** These are "nice to have" projects. The core roadmap (Phases 1-4) provides complete systems mastery. Phase 5 exists for continued growth and exploration.

---

## Optional Projects

### 1. BitTorrent Client

**Estimated Time:** 40-50 hours

**Overview:**
Peer-to-peer file sharing client implementing the BitTorrent protocol and Distributed Hash Table (DHT).

**Key Features:**
- BitTorrent protocol implementation (BEP 3)
- Distributed Hash Table for peer discovery (BEP 5)
- Piece selection algorithms (rarest-first, random-first, endgame mode)
- Integration with real BitTorrent network
- Tracker communication and peer exchange
- Upload/download rate limiting

**Skills Demonstrated:**
- Peer-to-peer networking
- Distributed hash tables
- File chunking and reassembly
- Protocol implementation

**Why Optional:**
- Demonstrates distributed systems, but CDN project already shows this
- P2P is less relevant to cloud engineering than client-server
- Time better spent on open source contributions

---

### 2. Custom Memory Allocators

**Estimated Time:** 30-40 hours

**Overview:**
High-performance memory allocators for different allocation patterns.

**Allocator Types:**
- **Buddy Allocator:** Power-of-2 sized allocations with efficient coalescing
- **Slab Allocator:** Frequently-used objects with minimal fragmentation
- **Pool Allocator:** Fixed-size allocations with O(1) alloc/free

**Key Features:**
- Performance benchmarks vs malloc/free
- Memory fragmentation analysis
- Thread-safe versions of each allocator
- Integration with custom containers

**Skills Demonstrated:**
- Memory management internals
- Performance optimization
- Low-level systems programming

**Why Optional:**
- Can use standard allocators in CDN project
- Interesting but not critical for cloud roles
- Good for deepening systems knowledge

---

### 3. HTTP/2 Server

**Estimated Time:** 30-40 hours

**Overview:**
HTTP/2 server implementation on top of the TCP stack from Phase 3.

**Key Features:**
- Binary framing layer
- Stream multiplexing (multiple requests over one connection)
- Header compression (HPACK)
- Server push
- Flow control
- Priority and dependency handling

**Skills Demonstrated:**
- Binary protocol implementation
- Advanced HTTP features
- Building on custom TCP stack

**Why Optional:**
- Already have HTTP/1.1 server from CSE 333
- May appear redundant on resume
- Good for protocol learning but not unique enough

---

### 4. gRPC Server

**Estimated Time:** 25-35 hours

**Overview:**
gRPC server implementation showing modern microservices RPC patterns.

**Key Features:**
- Protocol Buffers integration
- Unary RPC, server streaming, client streaming, bidirectional streaming
- Metadata and error handling
- Interceptors for logging/auth
- Load balancing client

**Skills Demonstrated:**
- Modern RPC frameworks
- Protocol Buffers
- Microservices patterns

**Why Optional:**
- Shows understanding of modern service communication
- Relevant to cloud/microservices roles
- Good complement to HTTP/REST knowledge

---

### 5. Service Mesh Data Plane (Mini-Envoy)

**Estimated Time:** 50-70 hours

**Overview:**
Layer 7 proxy with service mesh capabilities, similar to Envoy Proxy.

**Key Features:**
- Layer 7 load balancing (round-robin, least connections, consistent hashing)
- Health checking and circuit breaking
- Retry logic and timeouts
- TLS termination and mTLS
- Traffic splitting (canary, A/B testing)
- Service discovery integration
- Metrics and distributed tracing

**Skills Demonstrated:**
- Advanced networking (L7 proxying)
- Service mesh patterns
- Production-grade reliability features
- Cloud-native architecture

**Why Optional:**
- Extremely relevant to cloud engineering roles
- Shows understanding of Envoy/Istio internals
- Very impressive but time-intensive
- Could be done if pursuing infrastructure/platform roles

---

### 6. QUIC Protocol Implementation

**Estimated Time:** 60-80 hours

**Overview:**
Next-generation transport protocol (HTTP/3 foundation), UDP-based with built-in encryption.

**Key Features:**
- Connection establishment with 0-RTT
- Multiplexed streams without head-of-line blocking
- Connection migration (survive network changes)
- Built-in TLS 1.3
- Congestion control

**Skills Demonstrated:**
- Cutting-edge protocol implementation
- Understanding of TCP limitations and solutions
- Cryptography integration

**Why Optional:**
- Extremely advanced and unique
- Very few people build this
- Requires significant time investment
- Best for those pursuing networking specialization

---

## Recommended Prioritization

**If pursuing infrastructure/cloud engineering:**
1. Service Mesh Data Plane (shows Envoy/Istio understanding)
2. gRPC Server (microservices relevance)
3. Custom Memory Allocators (performance optimization)

**If pursuing distributed systems:**
1. BitTorrent Client (P2P patterns)
2. QUIC Protocol (next-gen networking)
3. gRPC Server (modern RPC)

**If pursuing networking specialization:**
1. QUIC Protocol (cutting-edge)
2. Service Mesh Data Plane (L7 networking)
3. HTTP/2 Server (protocol mastery)

**If maximizing resume impact:**
- Skip most of these, spend time on **more open source contributions** instead
- Production codebases >> greenfield solo projects

---

## When to Work on Phase 5

**Good times:**
- After completing Phases 1-4 and securing a job offer
- During employment (side projects for learning)
- When exploring a specific specialization
- For fun and continued growth

**Not recommended:**
- Before completing core roadmap (Phases 1-4)
- When time could be spent on open source contributions
- When preparing for interviews (focus on core projects instead)

---

## Links

- [Back to README](../../README.md)
