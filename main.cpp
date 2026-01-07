#include "network.cpp"

int main()
{
    Network n = create_network();
    int option;

    while (true)
    {
        cout << "\n===== NETWORK MENU =====\n";
        cout << "1. Add Routers\n";
        cout << "2. Add Links\n";
        cout << "3. Display Network Details\n";
        cout << "4. Display Links\n";
        cout << "5. Fail link\n";
        cout << "6. Restore link\n";
        cout << "7. Fail Router\n";
        cout << "8. Restore Router\n";
        cout << "9. Display routers details\n";
        cout << "10. Display shortest distances\n";
        cout << "11. Display shortest path\n";
        cout << "12. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (cin.fail()) // handle non-integer input
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (option)
        {
        case 1: // Add routers
            add_routers_in_network(n);
            break;

        case 2: // Add links
            add_links_in_network(n);
            break;

        case 3: // Display network details
            n.display_network_details();
            break;

        case 4: // Display links
            n.display_all_links_details();
            break;

        case 5: // Fail link
            fail_link_in_network(n);
            break;

        case 6: // Restore link
            restore_link_in_network(n);
            break;

        case 7: // Fail Router
            fail_router_in_network(n);
            break;

        case 8: // Restore router
            restore_router_in_network(n);
            break;

        case 9: // display routers details
            n.display_all_router_details();
            break;

        case 10: // display shortest distances
            n.display_all_shortest_distances();
            break;

        case 11: // display shortest path
            display_shortest_path(n);
            break;

        case 12: // Exit
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option! Please select 1-5.\n";
        }
    }

    return 0;
}