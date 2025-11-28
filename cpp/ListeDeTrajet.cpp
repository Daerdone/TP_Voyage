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

    cout << "Voulez vous créer un trajet simple (s) ou composé ? (c)" << endl;
    char type;
    cin >> type;

    char* start = new char[100];
    char* end = new char[100];
    char* transport = new char[100];
    
    if (type == 's')
    {
        cout << "Entrez votre trajet selon le format suivant :" << endl;
        cout << "<ville de départ>\n<ville d'arrivée>\n<moyen de transport>" << endl;
        
        cin >> start;
        cin >> end;
        cin >> transport;

        TrajetSimple* newTrajet = new TrajetSimple(start, end, transport);
        this->Add(newTrajet);

        
    }
    else if (type == 'c')
    {
        TrajetCompose* trajetCompose = new TrajetCompose();

        cout << "Entrez vos trajets selon le format suivant :" << endl;
        cout << "<ville de départ>\n<ville d'arrivée>\n<moyen de transport>" << endl;

        while (true)
        {
            cin >> start;

            if (strcmp(start, "stop") == 0)
            {
                break;
            }

            if (trajetCompose)

            // On vérifie que la ville de départ du nouveau trajet est bien la ville d'arrivée du précédent
            if (strcmp(start, trajetCompose->GetEnd()) != 0)
            {
                cout << "Erreur : la ville de départ du nouveau trajet doit être la même que la ville d'arrivée du précédent." << endl;
                cout << "Veuillez réessayer." << endl;
                continue;
            }

            cin >> end;
            cin >> transport;

            trajetCompose->AddTrajet(start, end, transport);

            cout << "Entrez 'stop' pour terminer ou une autre commande pour continuer." << endl;
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

    cout << "Entrez la ville de départ et d'arrivée selon le format suivant :" << endl;
    cout << "<ville de départ>\n<ville d'arrivée>" << endl;

    cin >> start;
    cin >> end;

    ListeDeTrajet* result = new ListeDeTrajet();
    this->Search(start, end, *result);

    cout << "Résultats de la recherche :" << endl;
    result->Print();

    delete[] start;
    delete[] end;
    delete result;
}

void ListeDeTrajet::Print() const
// Algorithme :
//
{
    elem* current = this->listTrajet;
    while (current != NULL)
    {
        (current->value)->Print();
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

    this->listTrajet = NULL;
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
    newElem->next = this->listTrajet;
    this->listTrajet = newElem;
}


void ListeDeTrajet::Search(const char* start, const char* end, ListeDeTrajet & result) const
// Algorithme :
//
{
    elem* current = this->listTrajet;
    while (current != NULL)
    {
        
        if ((!strcmp(current->value->GetStart(), start))
            && (!strcmp(current->value->GetEnd(), end)))
        {
            result.Add(current->value);
        }

        current = current->next;
    }
}