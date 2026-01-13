# Network Packet Routing Simulator Using Data Structures and Algorithms

## Project Overview
A C++ educational simulator demonstrating graph-based routing by implementing Dijkstra’s Shortest Path algorithm to compute routes in a network topology. The simulator models the algorithmic behavior underlying link-state routing (similar to OSPF’s SPF) without implementing the full OSPF protocol.

## Features

- Topology modeling via adjacency lists.
- Dijkstra single-source shortest-path implementation.
- Path reconstruction and forwarding-table generation.
- Packet forwarding simulation along computed routes.
- Link failure simulation and route recomputation.
- Deterministic test cases for evaluation.

## Technologies Used

- Language: C++ (C++11+ recommended)
- Build tools: g++, MSVC, or compatible C++ compiler
- Standard library containers: `vector`, `unordered_map`, `priority_queue`, etc.

## Algorithm Explanation

Dijkstra’s algorithm computes shortest paths from a source node to all other nodes in a weighted graph with non-negative edge weights. The algorithm maintains a priority queue of tentative distances, relaxes edges, and records predecessors for path reconstruction.

## How It Relates to OSPF

This simulator models the single-source SPF computation component used by OSPF routers: after building a topology (LSDB in OSPF), routers run an SPF algorithm to derive a shortest-path tree and determine next-hop forwarding entries. The simulator intentionally omits OSPF protocol mechanisms (LSA exchange, timers).

## Project Structure

Top-level files include `main.cpp` and headers such as `network.h`, `router.h`, `packet.h`. A recommended structure tree and explanations are provided in the repository's documentation.

## Build & Run Instructions

Build with g++:

```bash
g++ -std=c++11 -O2 main.cpp -o routing_sim
```

Run:

```bash
./routing_sim
```

On Windows with MSVC (Developer Command Prompt):

```powershell
cl /EHsc /O2 main.cpp
main.exe
```

Note: Adjust compilation commands according to your project layout and additional source files.

## Sample Usage

- Create a topology in code or via a simple input file.
- Run simulator to compute routes from source node 1.
- Inject packets and observe logged forwarding steps.
- Simulate a link failure and re-run to see updated routes.

## Limitations

- Not a full OSPF implementation; lacks LSA flooding, areas, and protocol mechanics.
- No real network interfaces; simulation only.
- Decrease-key not natively implemented in `std::priority_queue` (uses push-with-check approach).

## Future Improvements

- Incremental SPF updates.
- LSA simulation and LSDB modeling.
- Visualization tool.
- Performance optimizations and large-scale testing.

## License

[LICENSE placeholder] — choose an appropriate open-source license (e.g., MIT, Apache-2.0) before public release.