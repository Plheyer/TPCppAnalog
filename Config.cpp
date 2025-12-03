/*************************************************************************
                Config  - Gère la configuration du programme
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Config> (fichier Config.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Config.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool Config::LoadFromFile(const string& filename)
// Algorithme :
//  - Opens the configuration file given as parameter.
//  - Reads it line by line, skipping empty lines and comments.
//  - Splits each valid line into a key=value pair.
//  - Assigns values to the corresponding attributes (debug, BASE_URI).
//  - Returns false if the file could not be opened, true otherwise.
//
{
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open config file: " << filename << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }
        
        // Find the '=' separator
        size_t pos = line.find('=');
        if (pos == string::npos) {
            continue;
        }
        
        string key = trim(line.substr(0, pos));
        string value = trim(line.substr(pos + 1));
        
        // Parse values
        if (key == "debug") {
            debug = (value == "true" || value == "1" || value == "yes");
        } else if (key == "BASE_URI") {
            baseUri = value;
        }
    }
    
    file.close();
    return true;
} //----- Fin de LoadFromFile

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE
string Config::trim(const string& str)
// Algorithme :
//  - Removes spaces, tabs, and line breaks at the beginning and end
//    of the given string.
//  - Returns the cleaned substring.
//
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
} //----- Fin de Trim

//----------------------------------------------------- Méthodes protégées
