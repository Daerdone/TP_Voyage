#include "ListeDeTrajet.h"
#include <string.h>
#include <iostream>

using namespace std;

void PrintMenu();

int main()
{
    ListeDeTrajet catalogue = ListeDeTrajet();

    char command[100];
    PrintMenu();

    while (true)
    {
        cout << ">> ";
        cin >> command;

        if (!strcmp(command, "add"))
        {
            catalogue.AskNewTrajet();

        } else if (!strcmp(command, "print"))
        {
            catalogue.Print(1);
        } else if (!strcmp(command, "search"))
        {
            catalogue.AskSearch();
        } else if (!strcmp(command, "bye"))
        {
            cout << "Au revoir !" << endl;
            break;
        } else if (!strcmp(command, "help"))
        {
            PrintMenu();
        } else
        {
            cout << "Commande inconnue (\"" << command << "\"). Tapez \"help\" pour afficher la liste des commandes." << endl;
        }
    }

    return 0;
}

void PrintMenu()
{
    cout << endl << "Liste des commandes :" << endl;
    cout << "- add      : ajouter un trajet au catalogue" << endl;
    cout << "- print    : afficher tout le catalogue" << endl;
    cout << "- search   : chercher un trajet dans le catalogue" << endl;
    cout << "- help     : afficher ce menu" << endl;
    cout << "- bye      : quitter le programme" << endl << endl;
}

