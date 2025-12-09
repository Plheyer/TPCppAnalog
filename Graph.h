/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Graph> (fichier Graph.h) ----------------

#ifndef TPCPPANALOG_GRAPH_H
#define TPCPPANALOG_GRAPH_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Graph>
//
//
//------------------------------------------------------------------------

class Graph
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Attributs publics
    unordered_map<string, pair<unordered_map<string, int>, int>> hits;

//----------------------------------------------------- Méthodes publiques

    /**
     * @brief Charge et analyse un fichier de logs Apache.
     * @param filePath Le chemin du fichier de logs à analyser.
     * @param excludeRessourceFile Indique si les fichiers ressources doivent être exclus.
     * @param filterHourBegin Heure de début pour filtrer les entrées (valeur -1 pour désactiver).
     */
    void LoadFile (const string & filePath, bool excludeRessourceFile, int filterHourBegin);

    /**
     * @brief Calcule le Top N des documents les plus consultés.
     * @param N Le nombre de documents à afficher (par défaut 10).
     * @return affiche dans le stream out la liste du top 10.
     */
    void GetTopN (int N = 10) const;

    /**
     * @brief Génère le fichier de description du graphe au format GraphViz.
     * @param filename Le nom du fichier .dot à créer.
     * @return Vrai si le fichier a été généré avec succès.
     */
    bool GenerateGraphViz (const string& filename) const;


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Graph ( ){
        #ifdef MAP
            cout << "Appel au constructeur de <Graph>" << endl;
        #endif

        hits = unordered_map<string, pair<unordered_map<string, int>, int>>();
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Graph ( ){
        #ifdef MAP
            cout << "Appel au destructeur de <Graph>" << endl;
        #endif

        
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Graph>

#endif //TPCPPANALOG_GRAPH_H

