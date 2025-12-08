/*************************************************************************
                           Graph  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

#include <vector>
#include <string>
#include <utility>
#include <map>
//------------------------------------------------------ Include personnel
#include "Graph.h"
#include "ApacheLogStream.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Graph::LoadFile (const string & filePath, bool excludeRessourceFile, int filterHourEnd)
// Algorithme :
// 1. Ouvre le fichier filePath.
// 2. Initialise les filtres avec excludeRessourceFile et filterHourEnd.
// 3. Lit le fichier ligne par ligne et appelle la fonction de parsing/agrégation.
{
    ApacheLogStream logStream (filePath, "http://intranet-if.insa-lyon.fr");

    int linesProcessed = 0;

    LogEntry logEntry = logStream.getline();

    printf("Processing log file: %s\n", filePath.c_str());
    printf("IP, User Logname, Auth User, Timestamp, HTTP Method, Destination URL, HTTP Version, Status Code, Data Size, Referrer URL, User Agent\n");
    printf("%s, %s, %s, %d, %s, %s, %s, %d, %ld, %s, %s\n",
           logEntry.GetIpAddress().c_str(),
           logEntry.GetUserLogname().c_str(),
           logEntry.GetAuthUser().c_str(),
           logEntry.GetTimestamp(),
           logEntry.GetHttpMethod().c_str(),
           logEntry.GetDestinationUrl().c_str(),
           logEntry.GetHttpVersion().c_str(),
           logEntry.GetStatusCode(),
           logEntry.GetDataSize(),
           logEntry.GetReferrerUrl().c_str(),
           logEntry.GetUserAgent().c_str());
} //----- Fin de LoadFile

void Graph::GetTopN (int N) const
// Algorithme :
// 1. Copie hits dans une structure triable (ex: vector<pair<string, int>>).
// 2. Trie cette structure selon le nombre de hits (hits.second) par ordre décroissant.
// 3. Affiche les N premiers éléments sur la console.
{
} //----- Fin de GetTopN

bool Graph::GenerateGraphViz (const string& filename) const
// Algorithme :
// 1. Ouvre le fichier filename.dot.
// 2. Écrit le début du format GraphViz (digraph { ... ).
// 3. Parcourt la map hits pour écrire la définition de chaque nœud.
// 4. Parcourt les adjacents de hits pour écrire la définition de chaque arc pondéré.
// 5. Écrit la fin du format ( ... } ).
// 6. Retourne true si l'écriture a réussi.
{
    // 1. Ouvre le fichier filename.dot.
    string fullFilename = filename + ".dot";
    ofstream dotFile(fullFilename);

    if (!dotFile.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << fullFilename << " pour l'écriture." << endl;
        return false;
    }

    // 2. Écrit le début du format GraphViz (digraph { ... ).
    dotFile << "digraph {" << endl;
    dotFile << "  rankdir=\"LR\";" << endl; // Orientation de gauche à droite
    dotFile << "  node [shape=box, style=\"filled\", color=\"#B3D9FF\"];" << endl; // Style par défaut pour les nœuds internes

    // Pour gérer les URLs contenant des caractères spéciaux ou des espaces dans GraphViz
    // nous mapperons chaque URL à un identifiant de nœud unique (N1, N2, ...).
    // Nous utilisons std::map ici pour la cohérence des ID (bien qu'unordered_map soit possible).
    unordered_map<string, string> urlToNodeId;
    int nodeIdCounter = 0;

    // --- Étape 3: Définition de chaque nœud (basée sur toutes les clés de 'hits') ---

    for (const auto& pair : hits) {
        const string& url = pair.first;
        // Créer un identifiant de nœud unique
        string nodeId = "N" + to_string(++nodeIdCounter);
        urlToNodeId[url] = nodeId;

        // Écrire la définition du nœud : ID [label="URL", tooltip="Hits: X"]
        const int totalHits = pair.second.second;
        dotFile << "  " << nodeId << " [label=\"" << url << "\", tooltip=\"Hits: " << totalHits << "\"];" << endl;
    }

    // --- Étape 4: Définition de chaque arc pondéré (basée sur les adjacents) ---

    // Parcourir tous les nœuds sources dans hits
    for (const auto& referrerPair : hits) {
        const string& referrerUrl = referrerPair.first;
        // Récupérer l'ID du nœud source (il doit exister)
        const string& referrerId = urlToNodeId.at(referrerUrl);

        // La structure adjacente est referrerPair.second.first
        const auto& adjacents = referrerPair.second.first;

        // Parcourir toutes les destinations liées à ce référent (arcs sortants)
        for (const auto& destinationPair : adjacents) {
            const string& destinationUrl = destinationPair.first;
            const int weight = destinationPair.second; // Poids de l'arc (nombre de fois suivi)

            // Vérifier que le nœud de destination existe dans la map d'ID (doit être un nœud interne)
            if (urlToNodeId.count(destinationUrl)) {
                const string& destinationId = urlToNodeId.at(destinationUrl);

                // Écrire la définition de l'arc : source -> destination [label="poids"]
                dotFile << "  " << referrerId << " -> " << destinationId
                        << " [label=\"" << weight << "\", weight=" << weight << "];" << endl;
            } else {
                // CAS SPÉCIAL: Si la destination n'est pas dans 'hits' (ne devrait pas arriver si le parsing est correct)
                // Ou si vous avez des références à des ressources exclues.
                // On peut ajouter ce nœud 'manquant' si désiré, ou l'ignorer.
                // Ici, nous l'ignorons pour nous concentrer sur le graphe interne.
            }
        }
    }

    // GESTION DES RÉFÉRENTS EXTERNES (non présents comme clé dans 'hits')
    // Les référents externes ne sont pas stockés dans la structure hits dans cette implémentation
    // (car hits ne stocke que les URL internes visitées). Si le parsing capture et stocke
    // les arcs externes vers des cibles internes, cette logique devrait être ajoutée.
    // Étant donné la structure `hits`, nous assumons que seuls les liens internes sont capturés
    // et que les référents sont toujours des clés existantes dans `hits`.

    // 5. Écrit la fin du format ( ... } ).
    dotFile << "}" << endl;

    // 6. Retourne true si l'écriture a réussi.
    dotFile.close();
    cout << "Graphe GraphViz généré avec succès dans le fichier : " << fullFilename << endl;

    return true;
} //----- Fin de GenerateGraphViz

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
