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

## Algorithm Explanation

Dijkstra’s algorithm computes shortest paths from a source node to all other nodes in a weighted graph with non-negative edge weights. The algorithm maintains a priority queue of tentative distances, relaxes edges, and records predecessors for path reconstruction.

## How It Relates to OSPF

This simulator models the single-source SPF computation component used by OSPF routers: after building a topology (LSDB in OSPF), routers run an SPF algorithm to derive a shortest-path tree and determine next-hop forwarding entries. The simulator intentionally omits OSPF protocol mechanisms (LSA exchange, timers).


## Sample Usage

- Create a topology in code or via a simple input file.
- Run simulator to compute routes from source node 1.
- Inject packets and observe logged forwarding steps.
- Simulate a link failure and re-run to see updated routes.


## Contributing

Feel free to explore the repository and contribute to make IMS even better! If you have any questions or suggestions that would make this better, don't hesitate to reach out. Happy coding! 

## Contact

Salman Ahmed - [@Linkedin](https://www.linkedin.com/in/salman-ahmed-538897291/) - say2salmanahmed@gmail.com