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
    cout << "TC : ";
    Trajet::Print();
    cout << endl;
    listeDeTrajet->Print(2);
}

int TrajetCompose::GetNbrSubTrajets() const
// Algorithme :
//
{
    return listeDeTrajet->GetNbrTrajet();
}

void TrajetCompose::AddTrajet(const char * start, const char * end, const char * moyenDeTransport)
// Algorithme :
// Si la ville de départ du TrajetCompose n'est pas encore définie,
// on la définit avec la ville de départ du premier TrajetSimple ajouté.
// De même pour la ville d'arrivée.
// Dans tous les cas, on met à jour la ville d'arrivée avec celle du dernier TrajetSimple ajouté.
//
{
    TrajetSimple * trajet = new TrajetSimple(start, end, moyenDeTransport);
    
    if (this->start == NULL)
    {
        this->start = new char[100];
        strcpy(this->start, start);
    }
    if (this->end == NULL)
    {
        this->end = new char[100];
    }
    strcpy(this->end, end);
    listeDeTrajet->Add(trajet);
}

void TrajetCompose::WriteInOfstream(ofstream & file) const
// Algorithme :
// Écrit dans le flux file les informations du TrajetCompose
// selon le format défini dans modele_fichier.
{
    listeDeTrajet->WriteInOfstream(file);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose() : Trajet(1)
{
    #ifdef MAP
        cout << "Appel au constructeur de <TrajetCompose>" << endl;
    #endif

    listeDeTrajet = new ListeDeTrajet();
}

TrajetCompose::~TrajetCompose()
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

