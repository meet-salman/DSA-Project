#include "network.h"

void add_routers_in_network(Network &n)
{
    int noOfRouters;
    cout << "How many routers do you want to add? ";
    cin >> noOfRouters;

    for (int i = 0; i < noOfRouters; i++)
        n.add_router(n.get_no_of_routers());
}

void add_links_in_network(Network &n)
{
    int noOfLinks;
    cout << "How many links do you want to add? ";
    cin >> noOfLinks;

    for (int i = 1; i <= noOfLinks; i++)
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
            n.unidirectional_link(srcRouter, destRouter, distance, false, ((noOfLinks - i) == 0));
            break;

        case 2:
            n.bidirectional_link(srcRouter, destRouter, distance, true, ((noOfLinks - i) == 0));
            break;

        default:
            cout << "Invalid choice! No link added.\n";
        }
    }
}

void fail_link_in_network(Network &n)
{
    int srcRouter, destRouter, distance;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;
    cout << "Enter distance: ";
    cin >> distance;

    n.fail_link(srcRouter, destRouter, distance);
}

void restore_link_in_network(Network &n)
{
    int srcRouter, destRouter, distance;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;
    cout << "Enter distance: ";
    cin >> distance;

    n.restore_link(srcRouter, destRouter, distance);
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

void display_shortest_path(Network &n)
{
    int srcRouter, destRouter;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;

    n.display_router_shortest_path(srcRouter, destRouter);
}

void simulate_routing_from_router(Network &n)
{
    int srcRouter;
    cout << "Enter source router to simulate routing: ";
    cin >> srcRouter;

    n.simulate_routing(srcRouter);
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