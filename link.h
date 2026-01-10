#pragma once
#include "common.h"

class Link
{
private:
    int connectedRouter;
    int distance;
    bool isBiDirectional;
    bool status;

public:
    Link(int connectedRouter, int distance, bool isBiDirectional)
        : connectedRouter(connectedRouter), distance(distance),
          isBiDirectional(isBiDirectional), status(true)
    {
    }

    int getConnectedRouter() const { return connectedRouter; }
    int getDistance() const { return distance; }
    bool isBidirectional() const { return isBiDirectional; }
    bool isActive() const { return status; }

    void setStatus(bool newStatus) { status = newStatus; }

    bool validateLink(int connectedRouter, int distance)
    {
        if (connectedRouter != this->connectedRouter || distance != this->distance)
            return false;

        return true;
    }

    void displayLinkInfo() const
    {
        cout << "  -> Connected Router: " << connectedRouter
             << ", Distance: " << distance
             << ", Status: " << (status ? "ACTIVE" : "FAILED") << endl;
    }
};
