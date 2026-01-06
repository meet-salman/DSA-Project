#include "template.h"

class Link
{
public:
    int connectedRouter;
    int distance;
    bool isBiDirectional;
    bool status; // failed or alive

    Link(int connectedRouter, int distance, bool isBiDirectional) : connectedRouter(connectedRouter), distance(distance), status(true), isBiDirectional{isBiDirectional}
    {
        cout << "Router " << connectedRouter << " connected successfully!\n";
    }
};
