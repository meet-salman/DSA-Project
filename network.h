#include "router.h"

class Network
{
private:
    int id;
    string name;
    int linksInNetwork, activeLinksInNetwork;
    vector<Router> routers;
    vector<vector<Link>> links;
    vector<vector<int>> shortestDistances;
    vector<vector<vector<int>>> allPaths;

public:
    Network(int id, string name)
    {
        this->id = id;
        this->name = name;
        this->linksInNetwork = 0;
        this->activeLinksInNetwork = 0;

        cout << BG_BLUE << WHITE << BOLD
             << "------------------------------------------" << RESET << "\n";
        cout << BG_BLUE << WHITE << BOLD
             << "     NETWORK ESTABLISHED SUCCESSFULLY     " << RESET << "\n";
        cout << BG_BLUE << WHITE << BOLD
             << "------------------------------------------" << RESET << "\n";

        int noOfRouters;
        cout << "Enter no of routers to initialized: ";
        cin >> noOfRouters;

        // Initializing routers
        add_routers_in_bulk(0, noOfRouters - 1);

        display_network_details();
    }

    void display_network_details()
    {
        cout << BG_WHITE << BLUE << BOLD
             << "\n                 NETWORK                  " << RESET << "\n";
        cout << "------------------------------------------\n";

        cout << "Network ID: " << id << endl
             << "Network Name: " << name << endl
             << "Routers in Network: " << routers.size() << " Routers" << endl
             << "Actice Links in Network: " << activeLinksInNetwork << " Links" << endl;

        cout << "------------------------------------------\n";
    }

    int get_no_of_routers()
    {
        return routers.size();
    }

    // ---- Links Functions
    bool create_link(int srcRouter, int destRouter, int distance, bool isBiDirectional)
    {
        links.resize(routers.size());

        if (!validate_routers(srcRouter, destRouter))
            return false;

        // Validate distance
        if (distance <= 0)
        {
            cout << "Invalid distance\n";
            return false;
        }

        links[srcRouter].push_back(Link(destRouter, distance, isBiDirectional));
        return true;
        // cout << "\nrouter " << srcRouter << " -> " << links[destRouter][0].connectedRouter << " at dis " << links[destRouter][0].distance << " " << links[destRouter][0].status << endl;
    }

    void unidirectional_link(int srcRouter, int destRouter, int distance, bool isBiDirectional, bool isLast)
    {
        if (create_link(srcRouter, destRouter, distance, isBiDirectional))
        {
            cout << "Unidirectional link added from Router " << srcRouter
                 << " -> Router " << destRouter << endl;

            linksInNetwork++;
            activeLinksInNetwork++;

            if (isLast && activeLinksInNetwork >= 2)
                calculate_shortest_paths();
        }
    }

    void bidirectional_link(int srcRouter, int destRouter, int distance, bool isBiDirectional, bool isLast)
    {
        if (create_link(srcRouter, destRouter, distance, isBiDirectional) && create_link(destRouter, srcRouter, distance, isBiDirectional))
        {
            cout << "Bidirectional link added between Router " << srcRouter
                 << " <-> Router " << destRouter << endl;

            linksInNetwork++;
            activeLinksInNetwork++;

            if (isLast && activeLinksInNetwork >= 2)
                calculate_shortest_paths();
        }
    }

    void fail_link(int srcRouter, int destRouter, int distance)
    {
        if (!validate_routers(srcRouter, destRouter))
            return;

        bool biDirectional = false;
        bool failed = false;

        for (auto &link : links[srcRouter])
        {
            if (link.connectedRouter == destRouter && link.distance == distance)
            {
                if (link.status == 1)
                {
                    link.status = 0;
                    biDirectional = link.isBiDirectional;
                    failed = true;
                }
                else
                {
                    cout << "Router " << srcRouter
                         << (link.isBiDirectional ? " <-> " : " -> ")
                         << destRouter << " Link already failed!\n";
                    return;
                }
            }
        }

        if (biDirectional)
        {
            for (auto &link : links[destRouter])
            {
                if (link.connectedRouter == srcRouter && link.distance == distance)
                {
                    link.status = 0;
                    cout << "Router " << srcRouter << " <-> " << destRouter << " Linked failed!\n";
                }
            }
        }
        else
            cout << "Router " << srcRouter << " -> " << destRouter << " Linked failed!\n";

        if (failed)
        {
            activeLinksInNetwork--;
            calculate_shortest_paths();
        }
    }

    void restore_link(int srcRouter, int destRouter, int distance)
    {
        if (!validate_routers(srcRouter, destRouter))
            return;

        bool biDirectional = false;
        bool restored = false;

        for (auto &link : links[srcRouter])
        {
            if (link.connectedRouter == destRouter && link.distance == distance)
            {
                if (link.status == 0)
                {
                    link.status = 1;
                    biDirectional = link.isBiDirectional;
                    restored = true;
                }
                else
                {
                    cout << "Router " << srcRouter
                         << (link.isBiDirectional ? " <-> " : " -> ")
                         << destRouter << " Linked already active!\n";
                    return;
                }
            }
        }

        if (biDirectional)
        {
            for (auto &link : links[destRouter])
            {
                if (link.connectedRouter == srcRouter && link.distance == distance)
                {
                    link.status = 1;
                    cout << "Router " << srcRouter << " <-> " << destRouter << " Linked restored successfully!\n";
                }
            }
        }
        else
            cout << "Router " << srcRouter << " -> " << destRouter << " Linked restored successfully!\n";

        if (restored)
        {
            activeLinksInNetwork++;
            calculate_shortest_paths();
        }
    }

    void display_all_links_details()
    {
        cout << BG_WHITE << BLUE << BOLD
             << "\n              LINKS IN NETWORK                       " << RESET << "\n";
        cout << "-----------------------------------------------------\n";

        for (int i = 0; i < links.size(); i++)
        {
            cout << "Router " << i << " connections:\n";

            if (links[i].empty())
            {
                cout << "  No links.\n";
                continue;
            }

            for (const auto &link : links[i])
            {
                cout << "  -> Connected Router: " << link.connectedRouter
                     << ", Distance: " << link.distance
                     << ", Status: " << (link.status ? "ACTIVE" : "FAILED") << endl;
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------\n";
    }

    // ---- Router Functions
    bool validate_routers(int srcRouter, int destRouter)
    {
        if (srcRouter < 0 || srcRouter >= routers.size())
        {
            cout << "Invalid source router ID.\n";
            return false;
        }
        if (destRouter < 0 || destRouter >= routers.size())
        {
            cout << "Invalid destination router ID.\n";
            return false;
        }
        return true;
    }

    void add_router(int routerId)
    {
        routers.push_back(Router(routerId));
    }

    void add_routers_in_bulk(int startID, int endID)
    {
        for (int id = startID; id <= endID; id++)
            add_router(id);
    }

    void fail_router(int routerId)
    {
        if (routerId >= routers.size())
        {
            cout << "Invalid router ID.\n";
            return;
        }

        if (!routers[routerId].status)
        {
            cout << "Router " << routerId << " already failed!\n";
            return;
        }
        else
        {
            routers[routerId].status = 0;
            calculate_shortest_paths();
            cout << "Router " << routerId << " failed!\n";
        }
    }

    void restore_router(int routerId)
    {
        if (routerId >= routers.size())
        {
            cout << "Invalid router ID.\n";
            return;
        }

        if (routers[routerId].status)
        {
            cout << "Router " << routerId << " already active!\n";
            return;
        }
        else
        {
            routers[routerId].status = 1;
            calculate_shortest_paths();
            cout << "Router " << routerId << " restored successfully!\n";
        }
    }

    void display_all_router_details()
    {
        cout << "\n========== ROUTER DETAILS ==========\n";

        if (routers.empty())
        {
            cout << "No routers in the network.\n";
            return;
        }

        for (auto &router : routers)
            router.display_router_info();

        cout << "===================================\n";
    }

    // ---- Shortest path functions
    void calculate_shortest_paths()
    {
        shortestDistances.clear();
        allPaths.clear();

        for (int src = 0; src < routers.size(); src++)
        {
            // failed router
            if (routers[src].status == 0)
            {
                shortestDistances.push_back({});
                continue;
            }

            vector<bool> explored(routers.size(), false);
            vector<int> distance(routers.size(), INT_MAX);
            vector<int> parent(routers.size(), -1);

            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPQ;

            distance[src] = 0;
            minPQ.push({0, src});

            while (!minPQ.empty())
            {
                int currentNode = minPQ.top().second;
                int distanceToCurrentNode = minPQ.top().first;
                minPQ.pop();

                if (explored[currentNode])
                    continue;

                explored[currentNode] = true;

                for (auto &link : links[currentNode])
                {
                    if (link.status == 0)
                        continue;

                    int neighbour = link.connectedRouter;
                    int neighbourDistance = link.distance;
                    int distanceToNeighbour = distanceToCurrentNode + neighbourDistance;

                    if (!explored[neighbour] && routers[neighbour].status != 0 && distanceToNeighbour < distance[neighbour])
                    {
                        distance[neighbour] = distanceToNeighbour;
                        parent[neighbour] = currentNode;
                        minPQ.push({distanceToNeighbour, neighbour});
                    }
                }
            }
            // Add src Shortest Distances
            shortestDistances.push_back(distance);

            vector<vector<int>> distsFromSrc(routers.size());

            for (int dest = 0; dest < routers.size(); dest++)
            {
                if (distance[dest] == INT_MAX)
                    continue; // no path exists

                vector<int> path;
                int current = dest;

                // stop when reached at source
                while (current != -1)
                {
                    path.push_back(current);
                    current = parent[current];
                }

                reverse(path.begin(), path.end());
                distsFromSrc[dest] = path;
            }
            // Add src paths to all nodes
            allPaths.push_back(distsFromSrc);
        }
    }

    void display_router_shortest_path(int srcRouter, int destRouter)
    {
        cout << "\n======== SHORTEST PATH ========\n";
        cout << "Router " << srcRouter << " -> " << destRouter << endl;

        if (allPaths[srcRouter][destRouter].empty())
        {
            cout << "Unreachable!\n";
            return;
        }

        for (auto &next : allPaths[srcRouter][destRouter])
            cout << next << " ";
    }

    void display_all_shortest_distances()
    {
        cout << "\n======== SHORTEST DISTANCES ========\n";
        for (int src = 0; src < shortestDistances.size(); src++)
        {
            if (routers[src].status == 0)
                continue;

            cout << "Router " << src << ": ";
            for (auto &distance : shortestDistances[src])
            {
                cout << ((distance == INT_MAX) ? string("-") : to_string(distance)) << " ";
            }

            cout << endl;
        }
        cout << "======================================\n";
    }

    void simulate_routing(int srcRouter)
    {
        if (srcRouter < 0 || srcRouter >= routers.size())
        {
            cout << "Invalid source router.\n";
            return;
        }

        if (routers[srcRouter].status == 0)
        {
            cout << "Source router is FAILED. Cannot simulate routing.\n";
            return;
        }

        // Recalculate routing based on current network state
        // calculate_shortest_paths();

        cout << "\n===== ROUTING SIMULATION =====\n";
        cout << "Source Router: " << srcRouter << "\n\n";

        for (int dest = 0; dest < routers.size(); dest++)
        {
            if (dest == srcRouter)
                continue;

            if (routers[dest].status == 0 ||
                shortestDistances[srcRouter][dest] == INT_MAX)
            {
                cout << "Router " << dest << " : UNREACHABLE\n";
                continue;
            }

            // Print path
            for (int i = 0; i < allPaths[srcRouter][dest].size(); i++)
            {
                cout << allPaths[srcRouter][dest][i];
                if (i + 1 < allPaths[srcRouter][dest].size())
                    cout << " -> ";
            }

            cout << "   Distance: " << shortestDistances[srcRouter][dest] << "\n";
        }

        cout << "==============================\n";
    }
};