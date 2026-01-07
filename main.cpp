#include "network.cpp"

int main()
{
    Network n = create_network();
    int option;

    while (true)
    {
        cout << "\n===== NETWORK MENU =====\n";

        // Network Creation
        cout << "1. Add Routers\n";
        cout << "2. Add Links\n";

        // Display / View
        cout << "3. Display Network Details\n";
        cout << "4. Display All Router Details\n";
        cout << "5. Display All Link Details\n";

        // Failure & Recovery
        cout << "6. Fail Link\n";
        cout << "7. Restore Link\n";
        cout << "8. Fail Router\n";
        cout << "9. Restore Router\n";

        // Analysis
        cout << "10. Display Shortest Distances\n";
        cout << "11. Display Shortest Path\n";

        // Exit
        cout << "12. Exit\n";

        cout << "Enter your option: ";
        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (option)
        {
        case 1:
            add_routers_in_network(n);
            break;

        case 2:
            add_links_in_network(n);
            break;

        case 3:
            n.display_network_details();
            break;

        case 4:
            n.display_all_router_details();
            break;

        case 5:
            n.display_all_links_details();
            break;

        case 6:
            fail_link_in_network(n);
            break;

        case 7:
            restore_link_in_network(n);
            break;

        case 8:
            fail_router_in_network(n);
            break;

        case 9:
            restore_router_in_network(n);
            break;

        case 10:
            n.display_all_shortest_distances();
            break;

        case 11:
            display_shortest_path(n);
            break;

        case 12:
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option! Please select between 1 and 12.\n";
        }
    }

    return 0;
}