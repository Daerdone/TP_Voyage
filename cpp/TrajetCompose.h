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
//      -> Hérite de la classe Trajet
//      Implemente un trajet composée, qui gère une liste de trajets
//      simples avec possibilité d'ajouter des trajets à cette liste.
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Print() const;
    // Mode d'emploi :
    //      Affiche à l'utilisateurs les informations du TrajetCompose.
    //      (Ville d'arrivée et de départ) et toutes les informations des
    //      TrajetSimples composant le TrajetCompose.
    // Contrat :
    //

    int GetNbrSubTrajets() const;
    // Mode d'emploi :
    //      Retourne le nombre de TrajetSimples composant le TrajetCompose.
    // Contrat :
    //

    void AddTrajet(const char * start, const char * end, const char * moyenDeTransport);
    // Mode d'emploi :
    //		Crée un TrajetSimple et l'ajoute à la liste de trajets
	//		composant notre TrajetCompose.
    //      Met à jour les attributs start et end si nécessaire.
    // Contrat d'efficacité :
    //      Il faut que le trajet soit valide, c'est à dire que chaque
    //      ville de départ soit la ville d'arrivée du trajet précédent.

    void WriteInOfstream(ofstream & file) const;
    // Mode d'emploi :
    //      Écrit dans le flux file les informations du TrajetCompose
    //      selon le format défini dans modele_fichier.
    // Contrat :
    //      file doit être un flux valide et ouvert en écriture.

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ();
    // Mode d'emploi :
    // 		Initialise une ListeDeTrajet vide
    // Contrat :
    // 

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    //		Détruit la ListeDeTrajet associée au TrajetCompose
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    ListeDeTrajet *listeDeTrajet; // Liste des trajets simples composant le TrajetCompose
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif