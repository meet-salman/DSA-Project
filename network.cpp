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
    int srcRouter, destRouter, distance, option;

    cout << "\nEnter source router ID: ";
    cin >> srcRouter;

    cout << "Enter destination router ID: ";
    cin >> destRouter;

    cout << "Enter distance between routers: ";
    cin >> distance;

    cout << "\nSelect link type:\n";
    cout << "1. Unidirectional Link\n";
    cout << "2. Bidirectional Link\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option)
    {
    case 1:
        n.unidirectional_link(srcRouter, destRouter, distance, false);
        break;

    case 2:
        n.bidirectional_link(srcRouter, destRouter, distance, true);
        break;

    default:
        cout << "Invalid choice! No link added.\n";
    }
}

void fail_link_in_network(Network &n)
{
    int srcRouter, destRouter;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;

    n.fail_link(srcRouter, destRouter);
}

void restore_link_in_network(Network &n)
{
    int srcRouter, destRouter;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;

    n.restore_link(srcRouter, destRouter);
}

void fail_router_in_network(Network &n)
{
    int routerId;
    cout << "\nEnter router ID: ";
    cin >> routerId;
    n.fail_router(routerId);
}

void restore_router_in_network(Network &n)
{
    int routerId;
    cout << "\nEnter router ID: ";
    cin >> routerId;
    n.restore_router(routerId);
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