//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"
#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Print() const
// Algorithme :
//
{
    listeDeTrajet->Print();
}

void TrajetCompose::AddTrajet(const char * start, const char * end, const char * moyenDeTransport)
// Algorithme :
//
{
    TrajetSimple * trajet = new TrajetSimple(start, end, moyenDeTransport);
    
    strcpy(this->end, start);
    listeDeTrajet->Add(trajet);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose() : Trajet(NULL, NULL)
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetCompose>" << endl;
    #endif

    listeDeTrajet = new ListeDeTrajet;
}

TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <TrajetCompose>" << endl;
    #endif

    delete listeDeTrajet;
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

