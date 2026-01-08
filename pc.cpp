#include "pc.h"

PC *createPC()
{
    int id, routerID;
    cout << "Enter PC ID: ";
    cin >> id;
    cout << "Enter Connected Router ID: ";
    cin >> routerID;

    PC *newPC = new PC(id, routerID);
    cout << "Created PC " << id << ", connected to Router " << routerID << endl;
    return newPC;
}
