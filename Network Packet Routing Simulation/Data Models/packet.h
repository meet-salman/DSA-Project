#pragma once
#include "../Utilities & Constants/common.h"

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
        : id(packetID), sourcePC(src), destPC(dest),
          currentRouterID(currentRouterID), status(IN_TRANSIT)
    {
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

    void displayPacketDetails(bool isReceived = false) const
    {
        int colWidth = 12;
        int statusWidth = 12;

        cout << left << setw(colWidth) << sourcePC
             << left << setw(colWidth) << destPC;

        // Print path as 0->1->2
        string pathStr;
        for (int i = 0; i < path.size(); i++)
        {
            pathStr += to_string(path[i]);
            if (i + 1 < path.size())
                pathStr += "->";
        }
        cout << left << setw(30) << pathStr;

        // Determine status text and color
        string statusStr;
        string colorCode;

        switch (status)
        {
        case IN_TRANSIT:
            statusStr = "IN_TRANSIT";
            colorCode = YELLOW;
            break;
        case DELIVERED:
            if (isReceived)
                statusStr = "RECEIVED"; // change for received packets
            else
                statusStr = "DELIVERED";
            colorCode = GREEN;
            break;
        case DROPPED:
            statusStr = "DROPPED";
            colorCode = RED;
            break;
        }

        cout << colorCode << left << setw(statusWidth) << statusStr << RESET;
        cout << "\n";
    }
};
