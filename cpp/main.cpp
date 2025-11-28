#include "ListeDeTrajet.h"
#include <string.h>
#include <iostream>

using namespace std;

void PrintMenu();

int main()
{
    ListeDeTrajet* catalogue = new ListeDeTrajet();

    char* command = new char[100];

    PrintMenu();
    
    while (true)
    {
        cin >> command;

        if (!strcmp(command, "add"))
        {

        } else if (!strcmp(command, "print"))
        {

        } else if (!strcmp(command, "search"))
        {

        } else if (!strcmp(command, "bye"))
        {
            cout << "Au revoir !";
            break;
        } else
        {
            cout << "Commande inconnue." << endl;
            PrintMenu();
        }
    }

    return 0;
}

void PrintMenu()
{
    cout << "Liste des commandes :" << endl;
    cout << "- add      : ajouter un trajet au catalogue" << endl;
    cout << "- print    : afficher tout le catalogue" << endl;
    cout << "- search   : chercher un trajet dans le catalogue" << endl;
    cout << "- bye      : quitter le programme" << endl;
}