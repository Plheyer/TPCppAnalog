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
#include <algorithm>
//------------------------------------------------------ Include personnel
#include "Graph.h"
#include "ApacheLogStream.h"
#include "CouleurTTY.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool Graph::LoadFile (const string & filePath, bool excludeRessourceFile, int filterHourBegin, const string & baseUri)
// Algorithme :
// 1. Ouvre le fichier filePath.
// 2. Initialise les filtres avec excludeRessourceFile et filterHourBegin.
// 3. Lit le fichier ligne par ligne et appelle la fonction de parsing/agrégation.
{
    ApacheLogStream logStream (filePath, baseUri );

    if (logStream.fail()) {
        cerr << CouleurTTY(ROUGE) << "Erreur: Impossible d'ouvrir le fichier " << filePath << " pour la lecture." << CouleurTTY(RESET) << endl;
        return false;
    }

    if (excludeRessourceFile) {
        cout << CouleurTTY(JAUNE) << "Attention: Fichiers ressources exclus (CSS, JS, images) !" << CouleurTTY(RESET) << endl;
    }

    if (filterHourBegin != -1) {
        cout << CouleurTTY(JAUNE) << "Attention: Hits seulement entre " << filterHourBegin << "h et " << filterHourBegin + 1 << "h !" << CouleurTTY(RESET) << endl;
    }

    LogEntry* logEntry = nullptr;
    while (logStream.getline(logEntry)) {
        #ifdef MAP
            printf("Processing log file: %s\n", filePath.c_str());
            printf("IP, User Logname, Auth User, Timestamp, HTTP Method, Destination URL, HTTP Version, Status Code, Data Size, Referrer URL, User Agent\n");
            printf("%s, %s, %s, %d, %s, %s, %s, %d, %ld, %s, %s\n",
                logEntry->GetIpAddress().c_str(),
                logEntry->GetUserLogname().c_str(),
                logEntry->GetAuthUser().c_str(),
                logEntry->GetRequestedDatetime(),
                logEntry->GetHttpMethod().c_str(),
                logEntry->GetDestinationUrl().c_str(),
                logEntry->GetHttpVersion().c_str(),
                logEntry->GetStatusCode(),
                logEntry->GetDataSize(),
                logEntry->GetReferrerUrl().c_str(),
                logEntry->GetUserAgent().c_str());
        #endif

        if (excludeRessourceFile) {
            string url = logEntry->GetDestinationUrl();
            size_t dotPos = url.find_last_of('.');
            if (dotPos != string::npos) {
                string extension = url.substr(dotPos);
                if (extension == ".css" || extension == ".js" || extension == ".png" ||
                    extension == ".jpg" || extension == ".jpeg" || extension == ".gif" ||
                    extension == ".ico" || extension == ".svg") {
                    delete logEntry;
                    continue;
                }
            }
        }

        if (filterHourBegin != -1) {
            string datetime = logEntry->GetRequestedDatetime();
            size_t colonPos = datetime.find(':');
            if (colonPos != string::npos) {
                string hourStr = datetime.substr(colonPos + 1, 2);
                int hour = stoi(hourStr);
                if (hour != filterHourBegin) {
                    delete logEntry;
                    continue;
                }
            }
        }

        if (hits.find(logEntry->GetDestinationUrl()) == hits.end()) {
            hits[logEntry->GetDestinationUrl()] = make_pair(unordered_map<string, int>(), 0);
        }
        hits[logEntry->GetDestinationUrl()].second++;

        if (hits[logEntry->GetDestinationUrl()].first.find(logEntry->GetReferrerUrl()) == hits[logEntry->GetDestinationUrl()].first.end()) {
            hits[logEntry->GetDestinationUrl()].first[logEntry->GetReferrerUrl()] = 0;
        }
        hits[logEntry->GetDestinationUrl()].first[logEntry->GetReferrerUrl()]++;
        delete logEntry;
    }
    return true;    
} //----- Fin de LoadFile

void Graph::GetTopN (int n) const
// Algorithme :
// 1. Copie hits dans une structure triable (ex: vector<pair<string, int>>).
// 2. Trie cette structure selon le nombre de hits (hits.second) par ordre décroissant.
// 3. Affiche les N premiers éléments sur la console.
{
    // 1. Copier dans une structure triable
    vector<pair<string,int>> topList;
    unordered_map<
        string,
        pair<unordered_map<string,int>, int>
    >::const_iterator it;
    for (it = hits.begin(); it != hits.end(); ++it)
    {
        topList.push_back(make_pair(it->first, it->second.second));
    }

    // 2. Trier par ordre décroissant selon le nombre de hits
    sort(topList.begin(), topList.end(),
        [](const pair<string,int> &a,
        const pair<string,int> &b)
        {
            return a.second > b.second; // tri croissant
        });

    // 3. Afficher les N premiers
    int limit = min(n, static_cast<int>(topList.size()));
    for (int i = 0; i < limit; i++)
    {
        const pair<string, int> & p = topList[i];
        cout << CouleurTTY(VERT) << p.first
                  << CouleurTTY(RESET) << " (" << p.second << " hits)\n";
    }
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
        cerr << CouleurTTY(ROUGE) << "Erreur: Impossible d'ouvrir le fichier " << fullFilename << " pour l'écriture." << CouleurTTY(RESET) << endl;
        return false;
    }

    // 2. Écrit le début du format GraphViz (digraph { ... ).
    dotFile << "digraph {" << endl;
    dotFile << "  rankdir=\"LR\";" << endl; // Orientation de gauche à droite
    dotFile << "  node [shape=box, style=\"filled\", color=\"#B3D9FF\"];" << endl; // Style par défaut pour les nœuds internes

    // Pour gérer les URLs contenant des caractères spéciaux ou des espaces dans GraphViz
    // nous mapperons chaque URL à un identifiant de nœud unique (N1, N2, ...).
    // Nous utilisons map ici pour la cohérence des ID (bien qu'unordered_map soit possible).
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
                dotFile << "  " << destinationId << " -> " << referrerId
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
