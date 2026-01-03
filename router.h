#include "link.h"

class Router
{
public:
    int id;
    bool active; // failed or alive
    vector<Link> links;

    Router(int id) : id(id), active(true) {}

    void get_id() {}

    void get_status() {}

    void display_router_info() {}
};
