//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetSimple::Print() const
// Algorithme :
//
{
    Trajet::Print();
    cout << " (" << moyenDeTransport << ")" << endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple(const char* start, const char* end, const char* Transport) : Trajet(start, end)
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetSimple>" << endl;
    #endif

    strcpy(moyenDeTransport, Transport);
}


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <TrajetSimple>" << endl;
    #endif
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

