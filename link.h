#include "template.h"

class Link
{
public:
    int from, to;
    int distance;
    bool active; // failed or alive

    Link(int from, int to, int distance) : from(from), to(to), distance(distance), active(true) {}
};
