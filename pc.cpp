#pragma once
#include "network.h"
#include "pc.h"

void send_packet(Network &n)
{

    if (n.generate_pc_id() <= 1)
    {
        cout << "Packet can't be send yet!\n";
        return;
    }

    int srcPC, destPC;
    cout << "Enter Source PC ID: ";
    cin >> srcPC;
    cout << "Enter Destination PC ID: ";
    cin >> destPC;

    if (srcPC >= n.generate_pc_id())
    {
        cout << "Invalid Source PC ID\n";
        return;
    }

    if (destPC >= n.generate_pc_id())
    {
        cout << "Invalid Destination PC ID\n";
        return;
    }

    PC *src = n.get_pc(srcPC);
    Packet p = *src->generate_packet(srcPC, destPC);
    n.transmitt_packet(&p);
}

PC *createPC(int pcID, Network n)
{
    int routerID;
    cout << "Enter router ID to connect: ";
    cin >> routerID;

    if (routerID < 0 || routerID >= n.get_no_of_routers())
    {
        cout << "Invalid connected router ID.\n";
        return nullptr;
    }

    PC *newPC = new PC(pcID, routerID);
    cout << "Created PC " << pcID << ", connected to Router " << routerID << endl;
    return newPC;
}
