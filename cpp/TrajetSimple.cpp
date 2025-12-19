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
    cout << "TS : ";
    Trajet::Print();
    cout << " (" << moyenDeTransport << ")" << endl;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple (const TrajetSimple & unTrajetSimple ) : Trajet(unTrajetSimple.GetStart(), unTrajetSimple.GetEnd(), 0)
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
    #endif

    moyenDeTransport = new char[100];
    strcpy(moyenDeTransport, unTrajetSimple.GetMoyenDeTransport());
}

TrajetSimple::TrajetSimple(const char* start, const char* end, const char* Transport) : Trajet(start, end, 0)
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetSimple>" << endl;
    #endif

    moyenDeTransport = new char[100];
    strcpy(moyenDeTransport, Transport);
}

TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <TrajetSimple>" << endl;
    #endif

    delete [] moyenDeTransport;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées