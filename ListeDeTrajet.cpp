//---------- Réalisation de la classe <ListeDeTrajet> (fichier ListeDeTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "ListeDeTrajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void ListeDeTrajet::Add(const Trajet * newTrajet)
// Algorithme :
//
{
    elem* newElem = new elem;
    newElem->value = newTrajet;
    newElem->next = this->listTrajet;
    this->listTrajet = newElem;
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
        free(current);
        current = temp;
    }
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

