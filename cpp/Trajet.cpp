//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Trajet::Print ( ) const
// Algorithme :
//
{
    cout << start << " -> " << end;
} 

const char * Trajet::GetStart ( ) const
// Algorithme :
//
{
    return start;
} 

const char * Trajet::GetEnd ( ) const
// Algorithme :
//
{
    return end;
}

int Trajet::GetType() const
// Algorithme :
//
{
    return typeTrajet;
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

    delete [] start;
    delete [] end;
} 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

Trajet::Trajet (int type) : typeTrajet(type)
// Algorithme :
//
{
	#ifdef MAP
        cout << "Appel au constructeur de <Trajet>" << endl;
    #endif

	start = NULL;
	end = NULL;
}

Trajet::Trajet (const char *startIn, const char *endIn, int type) : typeTrajet(type)
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <Trajet>" << endl;
    #endif

    start = new char[100];
    end = new char[100];

	strcpy(start, startIn);
	strcpy(end, endIn);
}