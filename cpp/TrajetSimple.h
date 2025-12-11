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
//      -> Hérite de la classe Trajet.
//      Implemente le fonctionnement d'un trajet simple.
//      Un trajet simple possède une ville de départ et une d'arrivée
//      ainsi qu'un moyen de transport.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Print() const;
    // Mode d'emploi :
    //      Affiche à l'utilisateurs les informations du TrajetSimple.
    //      (Ville d'arrivée, de départ et moyen de transport)
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


    TrajetSimple (const char* start, const char* end, const char* moyenDeTransport);
    // Mode d'emploi :
    //		start -> Ville de départ du trajet
	// 		end -> Ville d'arrivée du trajet
    //      moyenDeTransport -> Moyen de transport utilisé pour le trajet.
    //
    //      Construit un TrajetSimple en copiant les chaînes de caractères
    //      passées en paramètre.
    // Contrat d'efficacité :
    //      Les paramètres start, end et moyenDeTransport ne sont pas NULL

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    //      Libère l'espace de la classe.
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    char* moyenDeTransport; //Moyen de transport utilisé lors du trajet.
};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TrajetSimple_H

