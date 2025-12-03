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
//------------------------------------------------------ Include personnel
#include "Graph.h"

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
    return true;
} //----- Fin de GenerateGraphViz

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
