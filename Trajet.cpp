//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Trajet::Print ( ) const
{
    cout << "Trajet de " << start << " à " << end << endl;
} 

const char * Trajet::GetStart ( ) const
{
    return start;
} 

const char * Trajet::GetEnd ( ) const
{
    return end;
} 

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
Trajet::~Trajet ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <Trajet>" << endl;
    #endif

} 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

Trajet::Trajet (const char* start, const char*end) 
    : start(start), end(end)
{
    #ifdef MAP
        cout << "Appel au constructeur de <Trajet>" << endl;
    #endif
}

