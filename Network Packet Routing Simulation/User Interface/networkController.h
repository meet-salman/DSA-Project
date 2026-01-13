#pragma once
#include "../Data Models/network.h"

// ===== Network UI Functions =====
Network createNetwork()
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

void addRoutersInNetwork(Network &n)
{
    int noOfRouters;
    cout << "How many routers do you want to add? ";
    cin >> noOfRouters;

    int startID = n.getNumberOfRouters();
    int endID = n.getNumberOfRouters() + noOfRouters;
    n.addRoutersInBulk(startID, endID);
}

void addLinksInNetwork(Network &n)
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

        bool isLast = (noOfLinks - i) == 0;

        switch (option)
        {
        case 1:
            n.unidirectionalLink(srcRouter, destRouter, distance, isLast);
            break;

        case 2:
            n.bidirectionalLink(srcRouter, destRouter, distance, isLast);
            break;

        default:
            cout << "Invalid choice! No link added.\n";
        }
    }
}

// ===== Link Management UI Functions =====
void updateLinkStatus(Network &n)
{
    int srcRouter, destRouter, distance;
    int choice;

    cout << BOLD << BLUE << "\n------ UPDATE LINK STATUS ------" << RESET << "\n";
    cout << "Enter Source Router ID: ";
    cin >> srcRouter;

    cout << "Enter Destination Router ID: ";
    cin >> destRouter;

    cout << "Enter Distance of the Link: ";
    cin >> distance;

    cout << "\nChoose Action:\n";
    cout << "1. Fail Link\n";
    cout << "2. Restore Link\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your option: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        n.failLink(srcRouter, destRouter, distance);
        break;
    case 2:
        n.restoreLink(srcRouter, destRouter, distance);
        break;
    case 0:
        return;
    default:
        cout << "Invalid option! Please select a valid option.\n";

        break;
    }

    cout << BOLD << BLUE << "--------------------------------" << RESET << "\n";
}

// ===== Router Management UI Functions =====
void updateRouterStatus(Network &n)
{
    int routerId;
    int choice;

    cout << BOLD << BLUE << "\n------ UPDATE ROUTER STATUS ------" << RESET << "\n";

    cout << "Enter Router ID: ";
    cin >> routerId;

    cout << "Choose Action:\n";
    cout << "1. Fail Router\n";
    cout << "2. Restore Router\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your option: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        n.failRouter(routerId);
        break;
    case 2:
        n.restoreRouter(routerId);
        break;
    case 0:
        return;
    default:
        cout << "Invalid option! Please select a valid option.\n";
        break;
    }

    cout << BOLD << BLUE "-----------------------------------\n";
}

// ===== Routing Analysis UI Functions =====
void displayShortestPath(Network &n)
{
    int srcRouter, destRouter;
    cout << "\nEnter source router: ";
    cin >> srcRouter;
    cout << "Enter destination router: ";
    cin >> destRouter;

    n.displayRouterShortestPath(srcRouter, destRouter);
}

void simulateRoutingFromRouter(Network &n)
{
    int srcRouter;
    cout << "Enter source router to simulate routing: ";
    cin >> srcRouter;

    n.simulateRouting(srcRouter);
}

// ===== PC UI Functions =====
void addPCInNetwork(Network &n)
{
    int numPCs;
    cout << "How many PCs do you want to add? ";
    cin >> numPCs;

    for (int i = 0; i < numPCs; i++)
    {
        int pcID = n.generatePCID();
        int routerID;

        cout << "\nEnter router ID to connect PC " << pcID << ": ";
        cin >> routerID;

        if (routerID < 0 || routerID >= n.getNumberOfRouters())
        {
            cout << RED << "Invalid router ID." << RESET << "\n";
            i--;
            continue;
        }

        PC *newPC = new PC(pcID, routerID);
        n.addPCInNetwork(newPC);

        cout << YELLOW << "Connecting PC " << pcID << " to Router " << routerID << RESET;
        loading(300);

        cout << "\033[2K\r";
        cout << GREEN << "PC " << pcID << " connected to Router " << routerID << RESET << "\n";
    }
}

// ===== Packet UI Functions =====
void sendPacket(Network &n)
{
    if (n.generatePCID() <= 1)
    {
        cout << RED << "Packet can't be sent yet! Need at least 2 PCs." << RESET << "\n";
        return;
    }

    int srcPC, destPC;
    cout << "Enter Source PC ID: ";
    cin >> srcPC;
    cout << "Enter Destination PC ID: ";
    cin >> destPC;

    if (srcPC >= n.generatePCID())
    {
        cout << RED << "Invalid Source PC ID" << RESET << "\n";
        return;
    }

    if (destPC >= n.generatePCID())
    {
        cout << RED << "Invalid Destination PC ID" << RESET << "\n";
        return;
    }

    PC *src = n.getPC(srcPC);
    Packet p = *src->generate_packet(srcPC, destPC);
    n.transmitPacket(&p);
}

void showPCPackets(Network &n)
{
    if (!n.arePcsInNetwork())
    {
        cout << RED << "No PCs in network." << RESET << "\n";
        return;
    }

    int pcID;
    cout << "Enter PC ID to view its packets: ";
    cin >> pcID;

    PC *pc = n.getPC(pcID);
    if (!pc)
    {
        cout << RED << "Invalid PC ID." << RESET << "\n";
        return;
    }

    pc->displayPackets(pcID);
}

// ===== Display Network UI Functions =====
void displayNetworkDetails(Network &n)
{
    int choice;

    while (true)
    {
        cout << BOLD << BLUE << "\n------ DISPLAY NETWORK DETAILS ------" << RESET << "\n";
        cout << "1. Full Network Summary\n";
        cout << "2. All Router Details\n";
        cout << "3. All Link Details\n";
        cout << "4. All PC Details\n";
        cout << "5. Display PC Packets\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            n.displayNetworkDetails();
            break;
        case 2:
            n.displayAllRouterDetails();
            break;
        case 3:
            n.displayAllLinksDetails();
            break;
        case 4:
            n.displayPCDetails();
            break;
        case 5:
            showPCPackets(n);
            break;
        case 0:
            return;
        default:
            cout << "Invalid option! Please select a valid option.\n";
            break;
        }
    }
}
