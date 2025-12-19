//---------- Réalisation de la classe <ListeDeTrajet> (fichier ListeDeTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <cstring>

//------------------------------------------------------ Include personnel
#include "ListeDeTrajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ListeDeTrajet::AskNewTrajet()
// Algorithme :
//
{
    cout << endl << "Voulez vous créer un trajet simple (s) ou composé ? (c)" << endl;
    cout << ">> ";
    char type;
    cin >> type;

    char start[100];
    char end[100];
    char transport[100];
    
    if (type == 's')
    {
        cout << endl << "Entrez votre trajet :" << endl;
        cout << ">> Ville de départ : ";
        cin >> start;
        cout << ">> Ville d'arrivée : ";
        cin >> end;
        cout << ">> Moyen de transport : ";
        cin >> transport;

        TrajetSimple* newTrajet = new TrajetSimple(start, end, transport);
        Add(newTrajet);

        cout << "Trajet ajouté au catalogue." << endl;

        
    }
    else if (type == 'c')
    {
        TrajetCompose* trajetCompose = new TrajetCompose();

        cout << endl << "Entrez vos trajets :" << endl;
        
        while (true)
        {
            cout << ">> Ville de départ : ";
            cin >> start;

            if (strcmp(start, "stop") == 0)
            {
                break;
            }

            // On vérifie que la ville de départ du nouveau trajet est bien la ville d'arrivée du précédent
            if (trajetCompose->GetEnd() != NULL && strcmp(start, trajetCompose->GetEnd()) != 0)
            {
                cout << "Erreur : la ville de départ du nouveau trajet doit être la même que la ville d'arrivée du précédent." << endl;
                cout << "Veuillez réessayer ou taper 'stop' pour arrêter." << endl;
                continue;
            }

            cout << ">> Ville d'arrivée : ";
            cin >> end;
            cout << ">> Moyen de transport : ";
            cin >> transport;

            trajetCompose->AddTrajet(start, end, transport);

            cout << endl << "Entrez 'stop' pour terminer ou un autre trajet pour continuer." << endl;
        }
        
        if (trajetCompose->GetEnd() != NULL)
        {
            Add(trajetCompose);
            cout << "Trajet ajouté au catalogue." << endl;
        }
        else
        {
            delete trajetCompose;
            cout << "Trajet vide, donc non ajouté au catalogue." << endl;
        }
    }
    else
    {
        cout << "Type de trajet inconnu (" << type << "). Retour au menu." << endl;
    }
}

void ListeDeTrajet::AskSearch() const
// Algorithme :
//
{
    char* start = new char[100];
    char* end = new char[100];

    cout << endl << "Recherche :" << endl;
    cout << ">> Ville de départ : ";
    cin >> start;
    cout << ">> Ville d'arrivée : ";
    cin >> end;

    cout << endl << "Résultats de la recherche :" << endl;
    this->Search(start, end);

    delete[] start;
    delete[] end;
}

void ListeDeTrajet::AskSave() const
// Algorithme :
//
{
    string filename;
    string criteria;

    cout << endl << "Sauvegarde du catalogue :" << endl;
    cout << ">> Entrez le nom du fichier : ";
    cin >> filename;

    cout << "Critères de sélection (a/s/c) : " << endl;
    cout << "- *a : tous les trajets" << endl;
    cout << "- *s : trajets simples uniquement" << endl;
    cout << "- *c : trajets composés uniquement" << endl;
    cout << "- ville départ = ville arrivée : selon la ville de départ et/ou d'arrivée" << endl;
    cout << "- [n,m] : selon les indices n et m des trajets dans le catalogue (ex: 0,3)" << endl;
    cout << ">> ";
    cin >> criteria;

    if (criteria.length() == 0)
    {
        cout << "Critères invalides. Retour au menu." << endl;
        return;
    }
    else if (criteria.at(0) == '*')
    {
        SaveToFile(filename, criteria[1]);
    }
    else if (criteria.at(0) == '[')
    {
        size_t commaPos = criteria.find(',');
        size_t endBracketPos = criteria.find(']');

        int n = stoi(criteria.substr(1, commaPos - 1));
        int m = stoi(criteria.substr(commaPos + 1, endBracketPos - commaPos - 1));

        SaveToFile(filename, n, m);
    }
    else {
        size_t equalPos = criteria.find('=');

        if (equalPos != string::npos)
        {
            string startCity = criteria.substr(0, equalPos);
            string endCity = criteria.substr(equalPos + 1);

            SaveToFile(filename, startCity, endCity);
        }
        else
        {
            cout << "Critères invalides. Retour au menu." << endl;
            return;
        }
    }
}

void ListeDeTrajet::Print(int indLvl) const
// Algorithme :
//
{
    elem* current = this->listTrajet;
    
    if (current == NULL)
    {
        for (int i = 0; i < indLvl; cout << "   ", i++) {} // Indentations
        cout << "- (Liste vide)" << endl;
        return;
    }

    while (current != NULL)
    {
        if (current->value != NULL)
        {
            for (int i = 0; i < indLvl; cout << "   ", i++) {} // Indentations
            cout << "- ";
            (current->value)->Print();
        }
        current = current->next;
    }
}

const char* ListeDeTrajet::GetStart() const
{
    return listTrajet->value->GetStart();
}

const char* ListeDeTrajet::GetEnd() const
{
    return endList->value->GetEnd();
}
    
void ListeDeTrajet::Add(const Trajet * newTrajet)
// Algorithme :
//
{
    elem* newElem = new elem;
    newElem->value = newTrajet;
    newElem->next = NULL;
    if (listTrajet == NULL)
    {
        listTrajet = newElem;
        endList = newElem;
    }
    else
    {
        endList->next = newElem;
        endList = newElem;
    }
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
ListeDeTrajet::ListeDeTrajet()
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <ListeDeTrajet>" << endl;
    #endif

    listTrajet = NULL;
    endList = NULL;
}

ListeDeTrajet::~ListeDeTrajet ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <ListeDeTrajet>" << endl;
    #endif

    elem* current = this->listTrajet;
    elem* temp;
    while (current != NULL)
    {
        temp = current->next;
        delete current->value;
        delete current;
        current = temp;
    }
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

void ListeDeTrajet::Search(const char* start, const char* end) const
// Algorithme :
// 1) Compte les trajets disponibles, les range dans un tableau et prépare
//    deux buffers : un marqueur d'utilisation (évite les cycles) et un
//    tableau courant représentant le chemin en construction.
// 2) Lance une recherche en profondeur (SearchPaths) depuis start vers end
//    en essayant chaque trajet qui commence par la ville courante et qui
//    n'a pas encore été utilisé. Chaque appel marque le trajet, descend
//    récursivement et dé-marque en remontant (backtracking).
// 3) Lorsqu'une destination end est atteinte avec au moins un segment,
//    affiche le chemin complet. Si aucun chemin n'est trouvé,
//    affiche un message dédié.
{
    int count = 0;
    elem* current = listTrajet;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    if (count == 0)
    {
        cout << "Aucun trajet disponible." << endl;
        return;
    }

    const Trajet** trajets = new const Trajet*[count];
    int* used = new int[count];
    const Trajet** path = new const Trajet*[count];

    current = listTrajet;
    int index = 0;
    while (current != NULL)
    {
        trajets[index] = current->value;
        used[index] = 0;
        current = current->next;
        index++;
    }

    bool found = false;
    SearchPaths(start, end, trajets, count, used, path, 0, found);

    if (!found)
    {
        cout << "Aucun trajet trouve." << endl;
    }

    delete[] trajets;
    delete[] used;
    delete[] path;
}

void ListeDeTrajet::SearchPaths(const char* current, const char* end, const Trajet** trajets, int count, int* used, const Trajet** path, int depth, bool & found) const
// Algorithme :
// Parcours en profondeur : pour chaque trajet partant de la ville courante
// et encore libre, on l'ajoute au chemin, on marque l'entrée comme utilisée,
// on poursuit depuis sa destination, puis on dé-marque en retour. Déclenche
// l'affichage dès qu'on atteint la ville cible avec un chemin non vide.
{
    if (strcmp(current, end) == 0 && depth > 0)
    {
        found = true;
        if (depth == 1)
        {
            path[0]->Print();
        }
        else
        {
            cout << "Trajet complexe :" << endl;
            for (int i = 0; i < depth; i++)
            {
                cout << "   ";
                path[i]->Print();
            }
        }
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (used[i])
        {
            continue;
        }

        const Trajet* trajet = trajets[i];
        const char* trajetStart = trajet->GetStart();
        const char* trajetEnd = trajet->GetEnd();

        if (trajetStart == NULL || trajetEnd == NULL)
        {
            continue;
        }

        if (strcmp(trajetStart, current) != 0)
        {
            continue;
        }

        used[i] = 1;
        path[depth] = trajet;
        SearchPaths(trajetEnd, end, trajets, count, used, path, depth + 1, found);
        used[i] = 0;
    }
}

