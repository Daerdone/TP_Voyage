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

    void AskSave() const;
    // Mode d'emploi :
    //      Demande à l'utilisateur de saisir les critères de sélection
    //      et le nom du fichier pour sauvegarder le catalogue dans un fichier.
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
    //      Recherche toutes les combinaisons de trajets du catalogue
    //      permettant d'aller de start à end, puis les affiche. Affiche
    //      un message dédié si aucun chemin n'est trouvé.
    // Contrat :
    //      start et end ne doivent pas être NULL. 

    void SearchPaths(const char* current, const char* end, const Trajet** trajets, int count, int* used, const Trajet** path, int depth, bool & found) const;
    // Mode d'emploi :
    //      Parcours en profondeur avec backtracking sur les trajets
    //      disponibles : explore chaque segment démarrant à current,
    //      marque l'entrée pour éviter les cycles, descend récursivement
    //      et affiche dès que end est atteint.
    // Contrat :
    //      trajets, used et path sont des tableaux de taille count,
    //      depth correspond à la profondeur courante, found passe à true
    //      dès qu'un chemin complet est identifié.

    void SaveToFile(const string & filename, const char & criteria) const;
    // Mode d'emploi :
    //      Sauvegarde le catalogue dans le fichier filename
    //      selon le critère spécifié (a, s ou c).
    // Contrat :
    //      filename et criteria ne doivent pas être NULL.

    void SaveToFile(const string & filename, int indice_deb, int indice_fin) const;
    // Mode d'emploi :
    //      Sauvegarde le catalogue dans le fichier filename
    //      selon les indices spécifiés.
    // Contrat :
    //      filename ne doit pas être NULL. indice_deb et indice_fin
    //      doivent être valides.

    void SaveToFile(const string & filename, const string & startCity, const string & endCity) const;

//----------------------------------------------------- Attributs protégés

    elem * listTrajet; // Pointeur vers le premier élément de la liste
    elem * endList; // Pointeur vers le dernier élément de la liste

};

//-------------------------------- Autres définitions dépendantes de <ListeDeTrajet>

#endif