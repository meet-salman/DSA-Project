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

        // PC Operations
        cout << "5. Send Packet\n";

        // Failure & Recovery
        cout << "6. Update Link Status\n";
        cout << "7. Update Router Status\n";

        // Analysis
        cout << "8. Display Shortest Distances\n";
        cout << "9. Display Shortest Path Between Two Routers\n";
        cout << "10. Simulate Routing from Source Router\n";

        // Exit
        cout << "11. Exit\n";

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
            displayNetworkDetails(n);
            break;

            // case 8:
            //     // showPCPackets(n);
            //     break;

        case 5:
            sendPacket(n);
            break;

        case 6:
            updateLinkStatus(n);
            break;

        case 7:
            updateRouterStatus(n);
            break;

        case 8:
            n.displayAllShortestDistances();
            break;

        case 9:
            displayShortestPath(n);
            break;

        case 10:
            simulateRoutingFromRouter(n);
            break;

        case 11:
            cout << "Exiting program. Goodbye!\n";
            return 0;

        default:
            cout << "Invalid option! Please select a valid option.\n";
        }
    }

    return 0;
}