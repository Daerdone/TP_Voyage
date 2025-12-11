//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet> :
//      Classe abstraite servant de brique de base pour construire les trajets simples et complexes,
//      en définissant les méthodes et arguments de base.
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Print() const;
    // Mode d'emploi :
    // 		Affiche dans le terminal la ville de départ et d'arrivée du trajet.
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

    // Les constructeurs sont protégées car la classe doit être abstraite.

    Trajet (const char* start, const char* end);
    // Mode d'emploi :
    //		start -> Ville de départ du trajet
	// 		end -> Ville d'arrivée du trajet
	// 
	// 		Alloue de la mémoire pour les attributs start et end
	//		et les initialise avec les données en paramètre.
	// Contrat d'efficacité :
    //      Les pointeurs start et end ne sont pas NULL.

    Trajet ();
    // Mode d'emploi :
	// 		Alloue de la mémoire pour les attributs start et end
	//		et les initialise à NULL.
	// Contrat :
    //

//----------------------------------------------------- Attributs protégés

    char* start; // Ville de départ du trajet
    char* end; // Ville de fin du trajet

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif