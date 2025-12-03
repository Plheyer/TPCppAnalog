/*************************************************************************
                ApacheLogStream  - Gère la lecture d'un flux de logs Apache
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <ApacheLogStream> (fichier ApacheLogStream.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ApacheLogStream.h"
#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
LogEntry ApacheLogStream::getline()
// Algorithme :
//
{
    string line;

    string ipAddress = "";
    int timestamp = 0;
    string httpMethod = "";
    int statusCode = 0;
    long dataSize = 0;
    string referrerUrl = "";
    string userAgent = "";

    *this >> line;

    printf("Parsing line: %s\n", line.c_str());

    return LogEntry(ipAddress, timestamp, httpMethod, statusCode, dataSize, referrerUrl, userAgent);
} //----- Fin de Afficher

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

ApacheLogStream::ApacheLogStream()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ApacheLogStream>" << endl;
#endif
} //----- Fin de ApacheLogStream


ApacheLogStream::~ApacheLogStream ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ApacheLogStream>" << endl;
#endif
} //----- Fin de ~ApacheLogStream


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
