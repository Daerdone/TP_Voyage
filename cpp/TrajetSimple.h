//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJET_SIMPLE_H )
#define TRAJET_SIMPLE_H

//--------------------------------------------------- Interfaces utilisées

#include "Trajet.h"
#include "ListeDeTrajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Print() const;
    // Mode d'emploi :
    
    // Contrat :

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


    TrajetSimple (const char* start, const char* end, const char* moyenDeTransport);
    // Mode d'emploi :
    // 
    // Contrat :
    //

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    char* moyenDeTransport;
};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TrajetSimple_H

