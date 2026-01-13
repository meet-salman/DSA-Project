#pragma once
#include "packet.h"

class PC
{
private:
    int pcID;
    int connectedRouterID;
    vector<Packet> sentPackets;
    vector<Packet> receivedPackets;
    bool status;

public:
    PC(int pcID, int routerID, bool active = true) : pcID(pcID), connectedRouterID(routerID), status(active)
    {
    }

    int get_PC_ID() const { return pcID; }
    int get_connected_router_ID() const { return connectedRouterID; }
    bool is_active() const { return status; }

    void set_connected_router(int routerID) { connectedRouterID = routerID; }
    void set_status(bool newStatus) { status = newStatus; }

    void addPacket(Packet *p, bool isSent)
    {
        if (p == nullptr)
            return;

        if (isSent)
            sentPackets.push_back(*p);
        else
            receivedPackets.push_back(*p);
    }

    void display_PC_details() const
    {
        cout << WHITE << left << setw(10) << pcID
             << WHITE << setw(20) << connectedRouterID
             << (status ? (GREEN "Active") : (RED "Inactive"))
             << RESET << "\n";
    }

    void displayPackets(int pcID)
    {
        int colWidth = 12;
        int statusWidth = 12;

        cout << RESET << "\n"
             << BG_WHITE << BLACK
             << "------------------------------------------------------------------" << RESET << "\n";

        cout << BG_WHITE << BLACK
             << "                          PACKETS IN PC " << pcID << "                         " << RESET << "\n";

        cout << BG_WHITE << BLACK
             << "------------------------------------------------------------------" << RESET << "\n";

        // -------- SENT PACKETS --------
        cout << RESET << "\n"
             << BG_WHITE << BLUE << BOLD
             << "                           SENT PACKETS                           "
             << RESET << "\n\n";

        if (sentPackets.empty())
        {
            cout << RED << "No sent packets yet.\n"
                 << RESET;
        }
        else
        {
            // Header
            cout << BLUE
                 << left << setw(colWidth) << "Src PC"
                 << left << setw(colWidth) << "Dest PC"
                 << left << setw(30) << "Path"
                 << left << setw(statusWidth) << "Status"
                 << RESET << "\n";

            cout << string(colWidth + colWidth + 30 + statusWidth, '-') << "\n";

            for (auto &p : sentPackets)
            {
                p.displayPacketDetails(false); // false = sent packets
            }
        }

        // -------- RECEIVED PACKETS --------
        cout << RESET << "\n"
             << BG_WHITE << GREEN << BOLD
             << "                         RECEIVED PACKETS                         "
             << RESET << "\n\n";

        if (receivedPackets.empty())
        {
            cout << RED << "No received packets yet.\n"
                 << RESET;
        }
        else
        {
            // Header
            cout << BLUE
                 << left << setw(colWidth) << "Src PC"
                 << left << setw(colWidth) << "Dest PC"
                 << left << setw(30) << "Path"
                 << left << setw(statusWidth) << "Status"
                 << RESET << "\n";

            cout << string(colWidth + colWidth + 30 + statusWidth, '-') << "\n";

            for (auto &p : receivedPackets)
            {
                p.displayPacketDetails(true); // true = received packets
            }
        }

        cout << "\n";
    }

    Packet *generate_packet(int srcPC, int destPC)
    {
        static int packetCounter = 1;
        Packet *p = new Packet(packetCounter++, srcPC, destPC, -1);
        return p;
    }
};
