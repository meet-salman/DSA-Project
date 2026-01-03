#include "link.h"

class Router
{
public:
    int id;
    bool active; // failed or alive
    vector<Link> links;

    Router(int id) : id(id), active(true) {}

    int get_id()
    {
        return id;
    }

    bool get_status()
    {
        return active;
    }

    void display_router_info()
    {
        cout << "Router ID: " << id << endl;
        cout << "Status   : " << (active ? "ACTIVE" : "FAILED") << endl;
    }
};
