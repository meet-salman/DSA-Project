#include "networkController.h"

int main()
{
    Network n = createNetwork();

    int noOfRouters;
    cout << "Enter number of routers to initialize: ";
    cin >> noOfRouters;
    n.initializeRouters(noOfRouters);

    int option;

    while (true)
    {
        cout << RESET << "\n"
             << BG_CYAN << BLACK
             << "=============================================" << RESET << "\n";

        cout << BG_CYAN << BLACK
             << "                  MAIN MENU                  " << RESET << "\n";

        cout << BG_CYAN << BLACK
             << "=============================================" << RESET << "\n";

        // Network Creation
        cout << "1. Add Router\n";
        cout << "2. Add Links\n";

        // Add PC
        cout << "3. Add PC\n";

        // Display / View
        cout << "4. Display Network Details\n";
        cout << "5. Display All Router Details\n";
        cout << "6. Display All Link Details\n";

        // PC Operations
        cout << "7. Display All PC Details\n";
        cout << "8. Display Packets in PC\n";
        cout << "9. Send Packet\n";

        // Failure & Recovery
        cout << "10. Fail Link\n";
        cout << "11. Restore Link\n";
        cout << "12. Fail Router\n";
        cout << "13. Restore Router\n";

        // Analysis
        cout << "14. Display Shortest Distances\n";
        cout << "15. Display Shortest Path Between Two Routers\n";
        cout << "16. Simulate Routing from Source Router\n";

        // Exit
        cout << "17. Exit\n";

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
            addRoutersInNetwork(n);
            break;

        case 2:
            addLinksInNetwork(n);
            break;

        case 3:
            addPCInNetwork(n);
            break;

        case 4:
            n.displayNetworkDetails();
            break;

        case 5:
            n.displayAllRouterDetails();
            break;

        case 6:
            n.displayAllLinksDetails();
            break;

        case 7:
            n.displayPCDetails();
            break;

        case 8:
            // showPCPackets(n);
            break;

        case 9:
            sendPacket(n);
            break;

        case 10:
            failLinkInNetwork(n);
            break;

        case 11:
            restoreLinkInNetwork(n);
            break;

        case 12:
            failRouterInNetwork(n);
            break;

        case 13:
            restoreRouterInNetwork(n);
            break;

        case 14:
            n.displayAllShortestDistances();
            break;

        case 15:
            displayShortestPath(n);
            break;

        case 16:
            simulateRoutingFromRouter(n);
            break;

        case 17:
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option! Please select a valid number.\n";
        }
    }

    return 0;
}