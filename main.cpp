#include "network.cpp"

int main()
{
    Network n = create_network();

    add_router_in_network(n);

    return 0;
}