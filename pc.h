#pragma once
#include "packet.h"

class PC
{
private:
    int pcID;
    int connectedRouterID;
    vector<Packet> sentPackets;
    vector<Packet> receivedPackets;
    bool status;

public:
    PC(int pcID, int routerID, bool active = true) : pcID(pcID), connectedRouterID(routerID), status(active)
    {
    }

    int get_PC_ID() const { return pcID; }
    int get_connected_router_ID() const { return connectedRouterID; }
    bool is_active() const { return status; }

    void set_connected_router(int routerID) { connectedRouterID = routerID; }
    void set_status(bool newStatus) { status = newStatus; }

    void addPacket(Packet *p, bool isSent)
    {
        if (p == nullptr)
            return;

        if (isSent)
            sentPackets.push_back(*p);
        else
            receivedPackets.push_back(*p);
    }

    void display_PC_details() const
    {
        cout << WHITE << left << setw(10) << pcID
             << WHITE << setw(20) << connectedRouterID
             << (status ? (GREEN "Active") : (RED "Inactive"))
             << RESET << "\n";
    }

    Packet *generate_packet(int srcPC, int destPC)
    {
        static int packetCounter = 1;
        Packet *p = new Packet(packetCounter++, srcPC, destPC, -1);
        return p;
    }
};
