#include "template.h"

class Link
{
public:
    int connectedRouter;
    int distance;
    bool status; // failed or alive

    Link(int connectedRouter, int distance) : connectedRouter(connectedRouter), distance(distance), status(true)
    {
        cout << "\nRouter " << connectedRouter << " connected successfully!";
    }
};
