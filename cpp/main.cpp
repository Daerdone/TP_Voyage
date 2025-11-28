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
            catalogue->AskNewTrajet();

        } else if (!strcmp(command, "print"))
        {
            catalogue->Print(1);
        } else if (!strcmp(command, "search"))
        {
            catalogue->AskSearch();
        } else if (!strcmp(command, "bye"))
        {
            cout << "Au revoir !" << endl;
            break;
        } else
        {
            cout << "Commande inconnue." << endl;
        }
        PrintMenu();
    }

    delete[] command;
    delete catalogue;

    return 0;
}

void PrintMenu()
{
    cout << endl << "Liste des commandes :" << endl;
    cout << "- add      : ajouter un trajet au catalogue" << endl;
    cout << "- print    : afficher tout le catalogue" << endl;
    cout << "- search   : chercher un trajet dans le catalogue" << endl;
    cout << "- bye      : quitter le programme" << endl;
    cout << ">> ";
}

