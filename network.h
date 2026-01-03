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

    void add_link(int u, int v, int w);
    void fail_router(int id);
    void fail_link(int u, int v);
    void restore_router(int id);
    void simulate_routing(int src);
};
