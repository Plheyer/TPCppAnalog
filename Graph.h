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
    unordered_map<string, pair<unordered_map<string, int>, int> hits;
    vector<pair<string, int>> topList;

//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    /**
     * @brief Traite les informations d'une ligne de log pour mettre à jour le graphe.
     * @param requestedUrl URL du document demandé (cible du hit).
     * @param refererUrl URL du référent (source du lien).
     * @param logHour L'heure de la requête pour la vérification du filtre -t.
     * @param isValidHit Booléen indiquant si le hit est valide après application des filtres -e et -t.
     * * @post Met à jour hits[requestedUrl].second (hits totaux).
     * @post Si refererUrl est interne, met à jour hits[refererUrl].first[requestedUrl] (poids de l'arc).
     */
    void LoadFile (const string & filePath, bool excludeRessourceFile, int filterHourEnd);

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
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Graph ( ){
    #ifdef MAP
        cout << "Appel au destructeur de <Graph>" << endl;
    #endif
}    // Mode d'emploi :
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

