#include "router.h"

class Network
{
private:
    int id;
    string name;
    int linksInNetwork, activeLinksInNetwork;
    set<int> routersInNetwork;
    vector<Router> routers;
    vector<vector<Link>> links;

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

    bool is_valid_router(int routerId)
    {
        return routersInNetwork.insert(routerId).second;
    }

    void add_router(int routerId)
    {
        if (is_valid_router(routerId))
            routers.push_back(Router(routerId));
        else
        {
            cout << "Router already exist\n";
            return;
        }
    }

    void add_routers_in_bulk(int startID, int endID)
    {
        for (int id = startID; id <= endID; id++)
            add_router(id);
    }

    void display_links()
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

    bool create_link(int srcRouter, int destRouter, int distance, bool isBiDirectional)
    {
        links.resize(routersInNetwork.size());

        // Validate router 1
        if (is_valid_router(srcRouter) && srcRouter >= 0)
        {
            cout << "Invalid router ID\n";
            routersInNetwork.erase(srcRouter);
            return false;
        }

        // Validate router 2
        if (is_valid_router(destRouter) && destRouter >= 0)
        {
            cout << "Invalid router ID\n";
            routersInNetwork.erase(destRouter);
            return false;
        }

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

    void unidirectional_link(int srcRouter, int destRouter, int distance, bool isBiDirectional)
    {
        if (create_link(srcRouter, destRouter, distance, isBiDirectional))
        {
            cout << "Unidirectional link added from Router " << srcRouter
                 << " -> Router " << destRouter << endl;

            linksInNetwork++;
            activeLinksInNetwork++;
        }
    }

    void bidirectional_link(int srcRouter, int destRouter, int distance, bool isBiDirectional)
    {
        if (create_link(srcRouter, destRouter, distance, isBiDirectional) && create_link(destRouter, srcRouter, distance, isBiDirectional))
        {
            cout << "Bidirectional link added between Router " << srcRouter
                 << " <-> Router " << destRouter << endl;

            linksInNetwork++;
            activeLinksInNetwork++;
        }
    }

    void fail_router(int id);

    void fail_link(int srcRouter, int destRouter)
    {
        bool biDirectional = false;

        for (auto &link : links[srcRouter])
        {
            if (link.connectedRouter == destRouter)
            {
                link.status = 0;
                biDirectional = link.isBiDirectional;
            }
        }

        if (biDirectional)
        {
            for (auto &link : links[destRouter])
            {
                if (link.connectedRouter == srcRouter)
                {
                    link.status = 0;

                    cout << "Router " << srcRouter << " <-> " << destRouter << " Linked failed successfully!\n";
                }
            }
        }
        else
            cout << "Router " << srcRouter << " -> " << destRouter << " Linked failed successfully!\n";

        activeLinksInNetwork--;
    }

    void restore_link(int srcRouter, int destRouter)
    {
        bool biDirectional = false;

        for (auto &link : links[srcRouter])
        {
            if (link.connectedRouter == destRouter)
            {
                link.status = 1;
                biDirectional = link.isBiDirectional;
            }
        }

        if (biDirectional)
        {
            for (auto &link : links[destRouter])
            {
                if (link.connectedRouter == srcRouter)
                {
                    link.status = 1;

                    cout << "Router " << srcRouter << " <-> " << destRouter << " Linked restored successfully!\n";
                }
            }
        }
        else
            cout << "Router " << srcRouter << " -> " << destRouter << " Linked restored successfully!\n";

        activeLinksInNetwork++;
    }

    void restore_router(int id);
    void simulate_routing(int src);
};
