#include "network.cpp"

int main()
{
    Network n = create_network();

    // add_router_in_network(n);
    // add_router_in_network(n);

    add_link_in_network(n);
    add_link_in_network(n);

    n.display_links();

    return 0;
}