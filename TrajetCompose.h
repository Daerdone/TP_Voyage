//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJET_COMPOSE_H )
#define TRAJET_COMPOSE_H

//--------------------------------------------------- Interfaces utilisées

#include "Trajet.h"
#include "ListeDeTrajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Print() const;
    // Mode d'emploi :
    
    // Contrat :

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


    TrajetCompose (ListeDeTrajet* ldt);
    // Mode d'emploi :
    // 
    // Contrat :
    // Il faut que la ListeDeTrajet ldt soit valide, c'est à dire que chaque ville d'arrivée soit la ville de départ du trajet suivant.

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    ListeDeTrajet* listeDeTrajet;
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TrajetCompose_H

