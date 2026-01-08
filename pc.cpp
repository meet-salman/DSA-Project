#pragma once
#include "network.h"
#include "pc.h"

void send_packet(Network &n)
{
    int srcPC, destPC;
    cout << "Enter Source PC ID: ";
    cin >> srcPC;
    cout << "Enter Destination PC ID: ";
    cin >> destPC;

    PC *src = n.get_pc(srcPC);
    Packet p = *src->generate_packet(srcPC, destPC);

    p.displayPacket();
}

PC *createPC(int pcID)
{
    int routerID;
    cout << "Enter router ID to connect: ";
    cin >> routerID;

    PC *newPC = new PC(pcID, routerID);
    cout << "Created PC " << pcID << ", connected to Router " << routerID << endl;
    return newPC;
}
