#pragma once
#include "packet.h"

class PC
{
private:
    int pcID;
    int connectedRouterID;
    bool status;

public:
    PC(int pcID, int routerID, bool active = true) : status(true)
    {
        this->pcID = pcID;
        this->connectedRouterID = routerID;
    }

    int get_PC_ID() const
    {
        return pcID;
    }

    int get_connected_router_ID() const
    {
        return connectedRouterID;
    }

    bool is_active() const
    {
        return status;
    }

    void set_connected_router(int routerID)
    {
        connectedRouterID = routerID;
    }

    void set_status(bool status)
    {
        status = status;
    }

    void display_PC_details() const
    {
        cout << "PC ID: " << pcID << endl;
        cout << "Connected Router ID: " << connectedRouterID << endl;
        cout << "Status: " << (status ? "Active" : "Inactive") << endl;
        cout << "-----------------------------" << endl;
    }

    Packet *generate_packet(int srcPC, int destPC)
    {
        static int packetCounter = 1;
        Packet *p = new Packet(packetCounter++, srcPC, destPC, -1);
        return p;
    }
};
