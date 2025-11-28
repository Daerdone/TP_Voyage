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
//
//
//------------------------------------------------------------------------

class ListeDeTrajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    

    void Print ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void AskNewTrajet();
    // Mode d'emploi :
    //      
    // Contrat :
    // 

    void AskSearch() const;
    // Mode d'emploi :
    //      
    // Contrat :
    // 

    const char* GetStart() const;
    // Mode d'emploi :
    //      
    // Contrat :
    // 

    const char* GetEnd() const;
    // Mode d'emploi :
    //      
    // Contrat :
    // 



//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    ListeDeTrajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ListeDeTrajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    void Add (const Trajet * newTrajet);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Search (const char* start, const char* end, ListeDeTrajet & result) const;
    // Mode d'emploi :
    //      
    // Contrat :
    // result est une ListeDeTrajet déjà allouée

    TrajetSimple* AskNewTrajetSimple() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés

    elem * listTrajet;

};

//-------------------------------- Autres définitions dépendantes de <ListeDeTrajet>

#endif // ListeDeTrajet_H

