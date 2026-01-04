#include "network.h"

void add_router_in_network(Network &n)
{
    int routerId;
    cout << "\nEnter Router ID: ";
    cin >> routerId;

    n.add_router(routerId);
}

void add_link_in_network(Network &n)
{
    int srcRouter, destRouter, distance;
    cout << "\nConnect router (id): ";
    cin >> srcRouter;

    cout << "to router (id): ";
    cin >> destRouter;

    cout << "at distance: ";
    cin >> distance;

    n.add_unidirectional_link(srcRouter, destRouter, distance);
}

Network create_network()
{
    int networkID;
    string networkName;

    cout << "Enter network ID: ";
    cin >> networkID;
    cout << "Enter network name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, networkName);

    Network n(networkID, networkName);

    return n;
}