#include "link.h"

class Router
{
public:
    int id;
    bool status; // failed or alive

    Router(int id) : id(id), status(true) {}

    int get_id()
    {
        return id;
    }

    bool get_status()
    {
        return status;
    }

    void display_router_info()
    {
        cout << "Router ID: " << id << endl;
        cout << "Status   : " << (status ? "ACTIVE" : "FAILED") << endl;
    }
};
