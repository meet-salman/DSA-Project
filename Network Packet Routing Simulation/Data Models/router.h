#pragma once
#include "../Utilities & Constants/common.h"

class Router
{
private:
    int id;
    bool status; // true = alive, false = failed

public:
    Router(int id) : id(id), status(true)
    {
    }

    int getId() const { return id; }
    bool getStatus() const { return status; }
    void setStatus(bool newStatus) { status = newStatus; }

    void displayRouterInfo() const
    {
        cout << BLUE << left << setw(15) << id;

        if (status)
        {
            cout << GREEN << setw(15) << "ALIVE";
        }
        else
        {
            cout << RED << setw(15) << "FAILED";
        }

        cout << RESET << "\n";
    }
};
