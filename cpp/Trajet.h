//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet> :
// Classe abstraite servant pour construire des trajets simples et complexes,
// en définissant les méthodes et arguments de base.
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Print() const;
    // Mode d'emploi :
    // 		Affiche la ville de départ et d'arrivée du trajet.
    // Contrat :
    //

    const char* GetStart() const;
    // Mode d'emploi :
    //		Renvoie la ville de départ du trajet.
    // Contrat :
    //

    const char* GetEnd() const;
    // Mode d'emploi :
    //		Renvoie la ville d'arrivée du trajet.
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    virtual ~Trajet ( );
    // Mode d'emploi :
    //		Libère les espaces alloués à start et end.
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Méthodes protégées

    Trajet (const char* start, const char* end);
    // Mode d'emploi :
    //		start -> Ville de départ du trajet (peut-être NULL)
	// 		end -> Ville d'arrivée du trajet (peut-être NULL)
	// 
	// 		Alloue de la mémoire pour les attributs start et end
	//		et les initialise avec les attributs en paramètre.
	// Contrat :
    //

//----------------------------------------------------- Attributs protégés

    char* start; // Ville de départ du trajet
    char* end; // Ville de fin du trajet

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif

