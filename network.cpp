#include "network.h"

void add_router_in_network(Network &n)
{
    int routerId;
    cout << "Enter Router ID: ";
    cin >> routerId;

    n.add_router(routerId);
}

Network create_network()
{
    int networkID;
    string networkName;

    cout << "Enter network ID: ";
    cin >> networkID;
    cout << "Enter network name: ";
    cin >> networkName;

    Network n(networkID, networkName);

    return n;
}