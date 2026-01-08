#include "template.h"

enum PacketStatus
{
    IN_TRANSIT,
    DELIVERED,
    DROPPED
};

class Packet
{
private:
    int id;
    int sourcePC;
    int destPC;
    int currentRouterID;
    vector<int> path;
    PacketStatus status;

public:
    Packet(int packetID, int src, int dest, int currentRouterID)
    {
        this->id = packetID;
        this->sourcePC = src;
        this->destPC = dest;
        this->currentRouterID = currentRouterID;
        this->status = IN_TRANSIT;
    }

    int getPacketID() const { return id; }
    int getSourcePC() const { return sourcePC; }
    int getDestPC() const { return destPC; }
    int getCurrentRouterID() const { return currentRouterID; }
    vector<int> getPath() const { return path; }
    PacketStatus getStatus() const { return status; }

    void setCurrentRouter(int routerID) { currentRouterID = routerID; }
    void setStatus(PacketStatus st) { status = st; }
    void addToPath(int routerID) { path.push_back(routerID); }

    void displayPacket() const
    {
        cout << "Packet ID: " << id << endl;
        cout << "Source PC: " << sourcePC << endl;
        cout << "Destination PC: " << destPC << endl;
        cout << "Current Router: " << currentRouterID << endl;

        cout << "Path: ";
        for (auto r : path)
            cout << r << " ";
        cout << endl;

        cout << "Status: ";
        switch (status)
        {
        case IN_TRANSIT:
            cout << "IN_TRANSIT";
            break;
        case DELIVERED:
            cout << "DELIVERED";
            break;
        case DROPPED:
            cout << "DROPPED";
            break;
        }
        cout << endl;
        cout << "-----------------------------" << endl;
    }
};
