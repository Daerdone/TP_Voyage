//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//
//
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Print() const;
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    const char* GetStart() const;
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    const char* GetEnd() const;
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    virtual ~Trajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Méthodes protégées

    Trajet (const char* start, const char* end);
    // Mode d'emploi :
    //
    // Contrat :
    //

//----------------------------------------------------- Attributs protégés

    const char* start; 
    const char* end;

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // Trajet_H

