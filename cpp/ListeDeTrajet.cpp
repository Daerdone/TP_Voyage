//---------- Réalisation de la classe <ListeDeTrajet> (fichier ListeDeTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "ListeDeTrajet.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ListeDeTrajet::AskNewTrajet()
{

    cout << endl << "Voulez vous créer un trajet simple (s) ou composé ? (c)" << endl;
    cout << ">>";
    char type;
    cin >> type;

    char* start = new char[100];
    char* end = new char[100];
    char* transport = new char[100];
    
    if (type == 's')
    {
        cout << endl << "Entrez votre trajet :" << endl;
        cout << ">> Ville de départ : ";
        cin >> start;
        cout << ">> Ville d'arrivée : ";
        cin >> end;
        cout << ">> Moyen de transport : ";
        cin >> transport;

        TrajetSimple* newTrajet = new TrajetSimple(start, end, transport);
        Add(newTrajet);
        
    }
    else if (type == 'c')
    {
        TrajetCompose* trajetCompose = new TrajetCompose();

        cout << endl << "Entrez vos trajets :" << endl;
        
        while (true)
        {
            cout << ">> Ville de départ : ";
            cin >> start;

            if (strcmp(start, "stop") == 0)
            {
                break;
            }

            // On vérifie que la ville de départ du nouveau trajet est bien la ville d'arrivée du précédent
            if (trajetCompose->GetEnd() != NULL && strcmp(start, trajetCompose->GetEnd()) != 0)
            {
                cout << "Erreur : la ville de départ du nouveau trajet doit être la même que la ville d'arrivée du précédent." << endl;
                cout << "Veuillez réessayer." << endl;
                continue;
            }

            cout << ">> Ville d'arrivée : ";
            cin >> end;
            cout << ">> Moyen de transport : ";
            cin >> transport;

            trajetCompose->AddTrajet(start, end, transport);

            cout << "Entrez 'stop' pour terminer ou un autre trajet pour continuer." << endl;
        }
        
        if (trajetCompose->GetEnd() != NULL)
        {
            Add(trajetCompose);
        }
    }

    delete[] start;
    delete[] end;
    delete[] transport;
}

void ListeDeTrajet::AskSearch() const
{
    char* start = new char[100];
    char* end = new char[100];

    cout << endl << "Recherche :" << endl;
    cout << ">> Ville de départ : ";
    cin >> start;
    cout << ">> Ville d'arrivée : ";
    cin >> end;

    cout << endl << "Résultats de la recherche :" << endl;
    this->Search(start, end);

    delete[] start;
    delete[] end;
}

void ListeDeTrajet::Print(int indLvl) const
// Algorithme :
//
{
    elem* current = this->listTrajet;
    
    while (current != NULL)
    {
        if (current->value != NULL)
        {
            for (int i = 0; i < indLvl; cout << "   ", i++) {}
            cout << "- ";
            (current->value)->Print();
        }
        current = current->next;
    }
}

const char* ListeDeTrajet::GetStart() const
{
    return listTrajet->value->GetStart();
}

const char* ListeDeTrajet::GetEnd() const
{
    elem* current = listTrajet;

    while (current->next != NULL)
    {   
        current = current->next;
    }
    
    return current->value->GetEnd();
}
    
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
ListeDeTrajet::ListeDeTrajet()
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <ListeDeTrajet>" << endl;
    #endif

    listTrajet = NULL;
    endList = NULL;
}


ListeDeTrajet::~ListeDeTrajet ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <ListeDeTrajet>" << endl;
    #endif

    elem* current = this->listTrajet;
    elem* temp;
    while (current != NULL)
    {
        temp = current->next;
        delete current->value;
        delete current;
        current = temp;
    }
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void ListeDeTrajet::Add(const Trajet * newTrajet)
// Algorithme :
//
{
    elem* newElem = new elem;
    newElem->value = newTrajet;
    newElem->next = NULL;
    if (listTrajet == NULL)
    {
        listTrajet = newElem;
        endList = newElem;
    }
    else
    {
        endList->next = newElem;
        endList = newElem;
    }
}


void ListeDeTrajet::Search(const char* start, const char* end) const
// Algorithme :
//
{
    elem* current = this->listTrajet;
    while (current != NULL)
    {
        if ((!strcmp(current->value->GetStart(), start))
            && (!strcmp(current->value->GetEnd(), end)))
        {
            current->value->Print();
        }

        current = current->next;
    }
}