#pragma once
#include "router.h"
#include "packet.h"
#include "pc.h"
#include "Link.h" // Or the correct file where class Link is defined

class Network
{
private:
    int id;
    string name;
    int linksInNetwork;
    int activeLinksInNetwork;
    int activeRoutersInNetwork;
    vector<Router> routers;
    vector<PC *> pcs;
    vector<vector<Link>> links;
    vector<vector<int>> shortestDistances;
    vector<vector<vector<int>>> allPaths;

public:
    Network(int id, string name) : id(id), name(name), linksInNetwork(0), activeLinksInNetwork(0), activeRoutersInNetwork(0) {}

    // ===== Initialization Methods =====
    void initializeRouters(int numberOfRouters)
    {
        addRoutersInBulk(routers.size(), numberOfRouters);

        cout << BG_BLUE << WHITE << BOLD
             << "\n------------------------------------------" << RESET << "\n";
        cout << BG_BLUE << WHITE << BOLD
             << "     NETWORK ESTABLISHED SUCCESSFULLY     " << RESET << "\n";
        cout << BG_BLUE << WHITE << BOLD
             << "------------------------------------------" << RESET << "\n";

        displayNetworkDetails();
    }

    // ===== Display Methods =====
    void displayNetworkDetails()
    {
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "                 NETWORK                  "
             << RESET << "\n";

        cout << BOLD << CYAN
             << "------------------------------------------"
             << RESET << "\n";

        cout << BLUE << "Network ID: " << RESET << id << "\n"
             << BLUE << "Network Name: " << RESET << name << "\n\n";

        // Routers info
        cout << GREEN << "Routers in Network: " << RESET
             << routers.size() << "\n";

        cout << GREEN << "Active Routers: " << RESET
             << activeRoutersInNetwork << "\n";

        cout << RED << "Failed Routers: " << RESET
             << (routers.size() - activeRoutersInNetwork) << "\n\n";

        // Links info
        cout << GREEN << "Links in Network: " << RESET
             << linksInNetwork << "\n";

        cout << GREEN << "Active Links: " << RESET
             << activeLinksInNetwork << "\n";

        cout << RED << "Failed Links: " << RESET
             << (linksInNetwork - activeLinksInNetwork) << "\n";

        cout << BOLD << CYAN
             << "------------------------------------------"
             << RESET << "\n";
    }

    void displayAllRouterDetails()
    {
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "             ROUTER DETAILS             "
             << RESET << "\n";

        if (routers.empty())
        {
            cout << BOLD << RED
                 << "No routers in the network."
                 << RESET << "\n";
            return;
        }

        cout << BOLD
             << BLUE << left << setw(15) << "Router ID"
             << GREEN << setw(15) << "Status"
             << RESET << "\n";

        cout << BOLD << CYAN
             << "---------------------------------------"
             << RESET << "\n";

        for (auto &router : routers)
        {
            router.displayRouterInfo();
        }

        cout << BOLD << CYAN
             << "---------------------------------------"
             << RESET << "\n";
    }

    void displayAllLinksDetails()
    {
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "                  LINKS IN NETWORK                   " << RESET << "\n";
        cout << BOLD << CYAN << "------------------------------------------------------" << RESET << "\n";

        for (int i = 0; i < links.size(); i++)
        {
            cout << BRIGHT_BLUE
                 << "Router " << i << " connections:"
                 << RESET << "\n";

            if (links[i].empty())
            {
                cout << "  No links.\n";
                continue;
            }

            for (const auto &link : links[i])
            {
                cout << "  -> Connected Router: " << link.getConnectedRouter()
                     << ", Distance: " << link.getDistance()
                     << ", Status: "
                     << (link.isActive() ? GREEN "ACTIVE" : RED "FAILED")
                     << RESET << endl;
            }
            cout << endl;
        }
        cout << BOLD << CYAN << "------------------------------------------------------" << RESET << "\n";
    }

    void displayPCDetails()
    {
        if (pcs.empty())
        {
            cout << RED << "No PCs in the network." << RESET << "\n";
            return;
        }

        // Table Title
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "                PCs DETAILS                  "
             << RESET << "\n\n";

        // Table Header
        cout << BLUE << BOLD
             << left << setw(10) << "PC ID"
             << setw(20) << "Connected Router"
             << setw(10) << "Status"
             << RESET << "\n";

        // Separator
        cout << CYAN
             << "---------------------------------------------"
             << RESET << "\n";

        // Table Rows
        for (auto &pc : pcs)
            pc->display_PC_details();

        // Footer Separator
        cout << CYAN
             << "---------------------------------------------"
             << RESET << "\n";
    }

    // ===== Router Management =====
    int getNumberOfRouters() { return routers.size(); }

    void addRouter(int routerId)
    {
        routers.push_back(Router(routerId));
        activeRoutersInNetwork++;

        cout << YELLOW << "Installing Router " << routerId << RESET;
        loading(0);

        cout << "\r"
             << GREEN << "Router " << routerId << " Installed successfully!"
             << RESET << "\n";
    }

    void addRoutersInBulk(int startID, int endID)
    {
        cout << "\n";
        for (int id = startID; id < endID; id++)
            addRouter(id);
    }

    bool validateRouters(int srcRouter, int destRouter)
    {
        if (srcRouter < 0 || srcRouter >= routers.size())
        {
            cout << RED << "Invalid source router ID." << RESET << "\n";
            return false;
        }
        if (destRouter < 0 || destRouter >= routers.size())
        {
            cout << RED << "Invalid destination router ID." << RESET << "\n";
            return false;
        }
        return true;
    }

    bool validateDistance(int distance)
    {
        if (distance <= 0)
        {
            cout << RED << "Invalid distance" << RESET << "\n";
            return false;
        }
        return true;
    }

    void failRouter(int routerId)
    {
        if (routerId >= routers.size())
        {
            cout << RED << "Invalid router ID." << RESET << "\n";
            return;
        }

        if (!routers[routerId].getStatus())
        {
            cout << "Router " << routerId
                 << RED << " ALREADY FAILED"
                 << RESET << "!\n";
            return;
        }

        routers[routerId].setStatus(false);
        activeRoutersInNetwork--;

        if (activeLinksInNetwork >= 2)
            calculateShortestPaths();

        cout << "Router " << routerId << " "
             << RED << "FAILED"
             << RESET << "!\n";
    }

    void restoreRouter(int routerId)
    {
        if (routerId >= routers.size())
        {
            cout << RED << "Invalid router ID." << RESET << "\n";
            return;
        }

        if (routers[routerId].getStatus())
        {
            cout << "Router " << routerId
                 << GREEN << " ALREADY ACTIVE"
                 << RESET << "!\n";

            return;
        }

        routers[routerId].setStatus(true);

        if (activeLinksInNetwork >= 2)
            calculateShortestPaths();

        cout << "Router " << routerId << " "
             << GREEN << "RESTORED SUCCESSFULLY"
             << RESET << "!\n";
    }

    // ===== Link Management =====
    bool createLink(int srcRouter, int destRouter, int distance, bool isBiDirectional)
    {
        links.resize(routers.size());

        if (!validateRouters(srcRouter, destRouter) || !validateDistance(distance))
            return false;

        links[srcRouter].push_back(Link(destRouter, distance, isBiDirectional));
        return true;
    }

    void unidirectionalLink(int srcRouter, int destRouter, int distance, bool isLast)
    {
        if (createLink(srcRouter, destRouter, distance, false))
        {
            cout << GREEN
                 << "Unidirectional link added from Router " << srcRouter
                 << " -> Router " << destRouter
                 << RESET << endl;

            linksInNetwork++;
            activeLinksInNetwork++;

            if (isLast && activeLinksInNetwork >= 2)
                calculateShortestPaths();
        }
    }

    void bidirectionalLink(int srcRouter, int destRouter, int distance, bool isLast)
    {
        if (createLink(srcRouter, destRouter, distance, true) &&
            createLink(destRouter, srcRouter, distance, true))
        {
            cout << GREEN
                 << "Bidirectional link added between Router " << srcRouter
                 << " <-> Router " << destRouter
                 << RESET << endl;

            linksInNetwork++;
            activeLinksInNetwork++;

            if (isLast && activeLinksInNetwork >= 2)
                calculateShortestPaths();
        }
    }

    void setLinkStatus(int srcRouter, int destRouter, int distance, bool newStatus)
    {
        if (!validateRouters(srcRouter, destRouter) || !validateDistance(distance))
            return;

        bool linkFound = false;
        bool biDirectional = false;

        // ---- Update src -> dest ----
        for (auto &link : links[srcRouter])
        {
            if (link.validateLink(destRouter, distance))
            {
                linkFound = true;

                if (link.isActive() == newStatus)
                {
                    cout << "Link " << srcRouter
                         << (link.isBidirectional() ? " <-> " : " -> ")
                         << destRouter << " "
                         << (newStatus ? GREEN : RED)
                         << (newStatus ? "ALREADY ACTIVE" : "ALREADY FAILED")
                         << RESET << "!\n";
                    return;
                }

                link.setStatus(newStatus);
                biDirectional = link.isBidirectional();
                break;
            }
        }

        // ---- Invalid link ----
        if (!linkFound)
        {
            cout << RED << "Invalid Link!" << RESET << "\n";
            return;
        }

        // ---- Update reverse link if bidirectional ----
        if (biDirectional)
        {
            for (auto &link : links[destRouter])
            {
                if (link.validateLink(srcRouter, distance))
                {
                    link.setStatus(newStatus);
                    break;
                }
            }
        }

        // ---- Message ----
        cout << "Link from Router " << srcRouter
             << (biDirectional ? " <-> " : " -> ")
             << "Router " << destRouter
             << " with distance " << distance << " "
             << (newStatus ? GREEN : RED)
             << (newStatus ? "RESTORED SUCCESSFULLY" : "FAILED")
             << RESET << "!\n";

        // ---- Update counts & routing ----
        if (newStatus)
            activeLinksInNetwork++;
        else
            activeLinksInNetwork--;

        if (activeLinksInNetwork >= 2)
            calculateShortestPaths();
    }

    void failLink(int srcRouter, int destRouter, int distance)
    {
        setLinkStatus(srcRouter, destRouter, distance, false);
    }

    void restoreLink(int srcRouter, int destRouter, int distance)
    {
        setLinkStatus(srcRouter, destRouter, distance, true);
    }

    // ===== PC Management =====
    void addPCInNetwork(PC *pc)
    {
        int connectedRouter = pc->get_connected_router_ID();

        if (connectedRouter < 0 || connectedRouter >= routers.size())
        {
            cout << "Invalid connected router ID.\n";
            delete pc;
            return;
        }
        pcs.push_back(pc);
    }

    PC *getPC(int pcID)
    {
        if (pcID < 0 || pcID >= pcs.size())
            return nullptr;

        return pcs[pcID];
    }

    int generatePCID()
    {
        return pcs.size();
    }

    // ===== Packet Functions =====
    void transmitPacket(Packet *p)
    {
        int srcPc = p->getSourcePC();
        int destPc = p->getDestPC();
        int srcPcRouter = pcs[p->getSourcePC()]->get_connected_router_ID();
        int destPcRouter = pcs[p->getDestPC()]->get_connected_router_ID();

        vector<int> path = allPaths[srcPcRouter][destPcRouter];

        cout << GREEN << "\nPacket sending started" << RESET;
        loading(500);
        if (path.empty())
        {
            cout << "\nPC " << srcPc << " -> PC " << destPc << " " << RED << "UNREACHABLE" << RESET << "!\n";
            cout << RED << "PACKET DROPPED!" << RESET << "\n";
            p->setStatus(DROPPED);
            return;
        }

        cout << BLUE << "\nPC " << srcPc << " -> Router " << srcPcRouter << RESET << "\n";

        for (int i = 0; i < path.size(); i++)
        {
            cout << "\033[2K\r";
            cout << BLUE << "Packet at Router " << path[i] << RESET << "\n";
            p->setCurrentRouter(path[i]);
            p->setStatus(IN_TRANSIT);

            if (i + 1 < path.size())
            {
                cout << YELLOW << "sending to Router " << path[i + 1] << RESET;
                loading(500);
            }
        }
        cout << YELLOW << "Router " << destPcRouter << " -> forwarding to PC " << destPc << RESET;
        loading(500);
        cout << "\033[2K\r";
        cout << BLUE << "Packet arrived at PC " << destPc << RESET << "\n";
        cout << GREEN << "Packet DELIVERED SUCCESSFULLY!" << RESET << "\n";

        p->setStatus(DELIVERED);
    }

    // ===== Shortest Path Functions (Dijkstra's Algorithm) =====
    void calculateShortestPaths()
    {
        shortestDistances.clear();
        allPaths.clear();

        for (int src = 0; src < routers.size(); src++)
        {
            if (!routers[src].getStatus())
            {
                shortestDistances.push_back({});
                allPaths.push_back({});
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
                    if (!link.isActive())
                        continue;

                    int neighbour = link.getConnectedRouter();
                    int neighbourDistance = link.getDistance();
                    int distanceToNeighbour = distanceToCurrentNode + neighbourDistance;

                    if (!explored[neighbour] && routers[neighbour].getStatus() &&
                        distanceToNeighbour < distance[neighbour])
                    {
                        distance[neighbour] = distanceToNeighbour;
                        parent[neighbour] = currentNode;
                        minPQ.push({distanceToNeighbour, neighbour});
                    }
                }
            }

            shortestDistances.push_back(distance);

            vector<vector<int>> pathsFromSrc(routers.size());

            for (int dest = 0; dest < routers.size(); dest++)
            {
                if (distance[dest] == INT_MAX)
                    continue;

                vector<int> path;
                int current = dest;

                while (current != -1)
                {
                    path.push_back(current);
                    current = parent[current];
                }

                reverse(path.begin(), path.end());
                pathsFromSrc[dest] = path;
            }

            allPaths.push_back(pathsFromSrc);
        }
    }

    void displayRouterShortestPath(int srcRouter, int destRouter)
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
        cout << "\n";
    }

    void displayAllShortestDistances()
    {
        int colWidth = 8;

        // Table Title
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "                SHORTEST DISTANCES                "
             << RESET << "\n\n";

        // Header row: Destination routers
        cout << BOLD << BLUE << left << setw(colWidth) << "Src\\Dest";
        for (int dest = 0; dest < shortestDistances.size(); dest++)
        {
            if (!routers[dest].getStatus())
                continue;
            cout << GREEN << setw(colWidth) << dest << RESET;
        }
        cout << "\n";

        // Separator row
        cout << BOLD << CYAN << left << "";
        for (int dest = 0; dest < shortestDistances.size(); dest++)
        {
            if (!routers[dest].getStatus())
                continue;
            cout << string(colWidth, '-'); // print exact width dashes
        }
        cout << RESET << "\n";

        // Table Rows
        for (int src = 0; src < shortestDistances.size(); src++)
        {
            if (!routers[src].getStatus())
                continue;

            // Source router column
            cout << BLUE << left << setw(colWidth) << src << RESET;

            // Distances to all destination routers
            for (int dest = 0; dest < shortestDistances[src].size(); dest++)
            {
                if (!routers[dest].getStatus())
                    continue;

                string distStr = (shortestDistances[src][dest] == INT_MAX) ? "-" : to_string(shortestDistances[src][dest]);
                cout << left << setw(colWidth) << distStr;
            }
            cout << "\n";
        }

        // Footer separator
        cout << BOLD << CYAN;
        cout << string(colWidth * routers.size() + 1, '-'); // match total width
        cout << RESET << "\n";
    }

    void simulateRouting(int srcRouter)
    {
        int colWidth = 15;
        int pathWidth = 30;
        int distWidth = 15;

        if (srcRouter < 0 || srcRouter >= routers.size())
        {
            cout << RED << "Invalid source router.\n"
                 << RESET;
            return;
        }

        if (!routers[srcRouter].getStatus())
        {
            cout << RED << "Router " << srcRouter << " is FAILED. Cannot simulate routing.\n"
                 << RESET;
            return;
        }

        cout << RESET << "\n"
             << BG_WHITE << BLACK
             << "------------------------------------------------------------" << RESET << "\n";
        cout << BG_WHITE << BLACK
             << "                     ROUTING SIMULATION                     " << RESET << "\n";
        cout << BG_WHITE << BLACK
             << "------------------------------------------------------------" << RESET << "\n\n";

        cout << BOLD << BLUE
             << left << setw(colWidth) << "Dest Router"
             << left << setw(pathWidth) << "Path"
             << left << setw(distWidth) << "Distance/Status"
             << RESET << "\n";

        cout << CYAN << string(colWidth + pathWidth + distWidth, '-') << RESET << "\n";

        // Print routing info
        for (int dest = 0; dest < routers.size(); dest++)
        {
            if (dest == srcRouter)
                continue;

            cout << left << setw(colWidth) << dest;

            if (!routers[dest].getStatus() || shortestDistances[srcRouter][dest] == INT_MAX)
            {
                cout << left << setw(pathWidth) << "-"
                     << RED << left << setw(distWidth) << "UNREACHABLE" << RESET << "\n";
                continue;
            }

            // Build path string
            string pathStr;
            for (int i = 0; i < allPaths[srcRouter][dest].size(); i++)
            {
                pathStr += to_string(allPaths[srcRouter][dest][i]);
                if (i + 1 < allPaths[srcRouter][dest].size())
                    pathStr += "->";
            }
            cout << left << setw(pathWidth) << pathStr;
            cout << left << setw(distWidth) << shortestDistances[srcRouter][dest] << "\n";
        }

        cout << CYAN << string(colWidth + pathWidth + distWidth, '-') << RESET << "\n";
    }
};