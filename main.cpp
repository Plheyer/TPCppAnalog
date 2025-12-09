/*************************************************************************
                           LogEntry  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

#include <limits>
#include <iostream>
#include <cstring>
#include "./CouleurTTY.h"
#include "./Graph.h"
#include "./Config.h"
using namespace std;
#define MAX_TAMPON 100

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayHelp() {
    cout << "Usage: analog [options] fichier_log" << endl;
    cout << "Options:" << endl;
    cout << "  -g fichier.dot : Génère un fichier GraphViz représentant le graphe" << endl;
    cout << "  -e             : Exclut les documents ayant une extension de type image, CSS ou JavaScript" << endl;
    cout << "  -t heure       : Ne considère que les hits qui sont dans le créneau horaire [heure, heure+1[" << endl;
    cout << endl;
    cout << "Exemple:" << endl;
    cout << "  analog -g graph.dot -e -t 10 anonymous.log" << endl;
}

int main(int argc, char* argv[])
{
    bool excludeOption = false;
    bool graphVizOption = false;
    bool hourOption = false;
    bool debug = false;
    int filterHour = -1;
    string graphVizFile, logFile, baseUri;

    Config config;
    config.LoadFromFile();
    debug = config.debug;
    baseUri = config.baseUri;
    
    // Parsing arguments
    int i = 1;
    while (i < argc) {
        string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            displayHelp();
            return 0;
        }
        else if (arg == "-e") {
            excludeOption = true;
            i++;
        }
        else if (arg == "-g") {
            if (i + 1 >= argc) {
                cerr << CouleurTTY(ROUGE) << "Erreur: L'option -g nécessite un nom de fichier" 
                     << CouleurTTY(RESET) << endl;
                displayHelp();
                return 1;
            }
            graphVizOption = true;
            graphVizFile = argv[i + 1];
            i += 2;
        }
        else if (arg == "-t") {
            if (i + 1 >= argc) {
                cerr << CouleurTTY(ROUGE) << "Erreur: L'option -t nécessite une heure (0-23)" 
                     << CouleurTTY(RESET) << endl;
                displayHelp();
                return 1;
            }
            hourOption = true;
            filterHour = atoi(argv[i + 1]);
            
            if (filterHour < 0 || filterHour > 23) {
                cerr << CouleurTTY(ROUGE) << "Erreur: L'heure doit être comprise entre 0 et 23" 
                     << CouleurTTY(RESET) << endl;
                return 1;
            }
            i += 2;
        }
        else if (arg[0] == '-') {
            cerr << CouleurTTY(ROUGE) << "Erreur: Option inconnue: " << arg 
                 << CouleurTTY(RESET) << endl;
            displayHelp();
            return 1;
        }
        else {
            logFile = arg;
            i++;
        }
    }
    
    // Checking if a log file has been given
    if (logFile.empty()) {
        cerr << CouleurTTY(ROUGE) << "Erreur: Aucun fichier log spécifié" 
             << CouleurTTY(RESET) << endl;
        displayHelp();
        return 1;
    }
    
    // DEBUG
    if (debug) {
        cout << CouleurTTY(CYAN) << "=== Configuration ===" << CouleurTTY(RESET) << endl;
        cout << "Fichier log: " << logFile << endl;
        
        if (excludeOption) {
            cout << CouleurTTY(JAUNE) << "Option -e activée: Exclusion des fichiers ressources" 
                 << CouleurTTY(RESET) << endl;
        }
        
        if (hourOption) {
            cout << CouleurTTY(JAUNE) << "Option -t activée: Filtre horaire [" 
                 << filterHour << "h - " << (filterHour + 1) << "h[" 
                 << CouleurTTY(RESET) << endl;
        }
        
        if (graphVizOption) {
            cout << CouleurTTY(JAUNE) << "Option -g activée: Génération du fichier " 
                 << graphVizFile << CouleurTTY(RESET) << endl;
        }
        
        cout << CouleurTTY(CYAN) << "=====================" << CouleurTTY(RESET) << endl << endl;
    }
    
    // Creating the graph and loading the logs
    Graph graph;
    
    cout << CouleurTTY(VERT) << "Chargement du fichier log..." << CouleurTTY(RESET) << endl;
    if (!graph.LoadFile(logFile, excludeOption, hourOption ? filterHour : -1)) {
        return 1;
    }
    
    // Displaying the top 10
    cout << endl << CouleurTTY(CYAN) << "=== Top 10 des documents les plus consultés ===" 
         << CouleurTTY(RESET) << endl;
    graph.GetTopN();
    
    // Generating GraphViz if asked
    if (graphVizOption) {
        cout << endl << CouleurTTY(VERT) << "Génération du fichier GraphViz..." 
             << CouleurTTY(RESET) << endl;
        if (graph.GenerateGraphViz(graphVizFile)) {
            cout << CouleurTTY(VERT) << "Fichier " << graphVizFile 
                 << " généré avec succès" << CouleurTTY(RESET) << endl;
            cout << "Vous pouvez générer l'image avec: dot -Tpng " << graphVizFile 
                 << " -o graph.png" << endl;
        } else {
            cerr << CouleurTTY(ROUGE) << "Erreur lors de la génération du fichier GraphViz" 
                 << CouleurTTY(RESET) << endl;
            return 1;
        }
    }
    return 0;
}