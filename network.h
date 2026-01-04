#include "router.h"

class Network
{
private:
    int id;
    string name;
    vector<Router> routers;
    set<int> routersInNetwork;
    vector<vector<Link>> links;

public:
    Network(int id, string name)
    {
        this->id = id;
        this->name = name;

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
             << "Links in Network: " << links.size() << " Links" << endl;

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

    void add_link(int routerOne, int routerTwo, int distance)
    {
        links.resize(routersInNetwork.size());

        // Validate router 1
        if (is_valid_router(routerOne) && routerOne >= 0)
        {
            cout << "Invalid router ID\n";
            routersInNetwork.erase(routerOne);
            return;
        }

        // Validate router 2
        if (is_valid_router(routerTwo) && routerTwo >= 0)
        {
            cout << "Invalid router ID\n";
            routersInNetwork.erase(routerTwo);
            return;
        }

        // Validate distance
        if (distance <= 0)
        {
            cout << "Invalid distance\n";
            return;
        }

        links[routerOne].push_back(Link(routerOne, distance));
        links[routerTwo].push_back(Link(routerTwo, distance));

        // cout << "\nrouter " << routerOne << " -> " << links[routerTwo][0].connectedRouter << " at dis " << links[routerTwo][0].distance << " " << links[routerTwo][0].status << endl;
        // cout << "\nrouter " << routerTwo << " -> " << links[routerOne][0].connectedRouter << " at dis " << links[routerOne][0].distance << " " << links[routerOne][0].status << endl;
    }

    void fail_router(int id);
    void fail_link(int u, int v);
    void restore_router(int id);
    void simulate_routing(int src);
};
