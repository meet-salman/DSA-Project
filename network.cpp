#include "network.h"

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