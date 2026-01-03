#include "router.h"

class Network
{
private:
    int n;
    vector<vector<Link>> adj;
    vector<Router> routers;

public:
    Network(int n);
    void add_link(int u, int v, int w);
    void fail_router(int id);
    void fail_link(int u, int v);
    void restore_router(int id);
    void simulate_routing(int src);
};
