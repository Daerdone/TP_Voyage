//---------- Interface de la classe <ListeDeTrajet> (fichier ListeDeTrajet.h) ----------------
#if ! defined ( ListeDeTrajet_H )
#define ListeDeTrajet_H

//--------------------------------------------------- Interfaces utilisées

#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef struct elem {
    const Trajet * value;
    elem * next;
} elem;

//------------------------------------------------------------------------
// Rôle de la classe <ListeDeTrajet>
//      Classe représentant une liste de trajets.
//      Permet d'ajouter des trajets, d'afficher la liste,
//      et de rechercher des trajets entre deux villes.
//------------------------------------------------------------------------

class ListeDeTrajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void Print (int indLvl) const;
    // Mode d'emploi :
    //      indLvl -> Niveau d'indentation pour l'affichage
    //
    //      Affiche la liste des trajets avec un niveau d'indentation donné.
    // Contrat :
    //      

    void AskNewTrajet();
    // Mode d'emploi :
    //      Demande à l'utilisateur de saisir un nouveau trajet.
    // Contrat :
    // 

    void AskSearch() const;
    // Mode d'emploi :
    //      Demande à l'utilisateur de saisir les villes de départ
    //      et d'arrivée pour une recherche.
    // Contrat :
    // 

    const char* GetStart() const;
    // Mode d'emploi :
    //      Retourne la ville de départ du premier trajet de la liste.
    //      Si la liste est vide, retourne NULL.

    const char* GetEnd() const;
    // Mode d'emploi :
    //      Retourne la ville d'arrivée du dernier trajet de la liste.
    //      Si la liste est vide, retourne NULL.

    void Add (const Trajet * newTrajet);
    // Mode d'emploi :
    //    Ajoute un nouveau trajet à la fin de la liste.
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    ListeDeTrajet ( );
    // Mode d'emploi :
    //      Initialise une liste de trajets vide.
    // Contrat :
    //

    virtual ~ListeDeTrajet ( );
    // Mode d'emploi :
    //      Libère la mémoire allouée pour la liste des trajets.
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void Search (const char* start, const char* end) const;
    // Mode d'emploi :
    //      Recherche des trajets entre deux villes données et les affiche.
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés

    elem * listTrajet; // Pointeur vers le premier élément de la liste
    elem * endList; // Pointeur vers le dernier élément de la liste

};

//-------------------------------- Autres définitions dépendantes de <ListeDeTrajet>

#endif