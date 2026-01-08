#include "network.cpp"
#include "pc.cpp"

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

        // Add PC
        cout << "3. Add PC\n";

        // Display / View
        cout << "4. Display Network Details\n";
        cout << "5. Display All Router Details\n";
        cout << "6. Display All Link Details\n";

        // PC Operations
        cout << "7. Display All PC's Details\n";

        // Failure & Recovery
        cout << "8. Fail Link\n";
        cout << "9. Restore Link\n";
        cout << "10. Fail Router\n";
        cout << "11. Restore Router\n";

        // Analysis
        cout << "12. Display Shortest Distances\n";
        cout << "13. Display Shortest Path\n";
        cout << "14. Simulate Routing from Source\n";

        // Exit
        cout << "15. Exit\n";

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
        {
            PC *newPC = createPC();
            n.add_pc_in_network(newPC);
        }
        break;

        case 4:
            n.display_network_details();
            break;

        case 5:
            n.display_all_router_details();
            break;

        case 6:
            n.display_all_links_details();
            break;

        case 7:
            n.display_pc_details();
            break;

        case 8:
            fail_link_in_network(n);
            break;

        case 9:
            restore_link_in_network(n);
            break;

        case 10:
            fail_router_in_network(n);
            break;

        case 11:
            restore_router_in_network(n);
            break;

        case 12:
            n.display_all_shortest_distances();
            break;

        case 13:
            display_shortest_path(n);
            break;

        case 14:
            simulate_routing_from_router(n);
            break;

        case 15:
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option! Please select a valid number.\n";
        }
    }

    return 0;
}