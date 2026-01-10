#pragma once
#include "common.h"

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
    PacketStatus getStatus() const { return status; }

    void setCurrentRouter(int routerID) { currentRouterID = routerID; }
    void setStatus(PacketStatus st) { status = st; }
};
