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
#include <regex>
#include <string>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ApacheLogStream.h"
#include "LogEntry.h"
#include "CouleurTTY.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool ApacheLogStream::getline(LogEntry*& entry)
// Algorithme :
//
{
    char line[MAX_BUFFER];
    if (!ifstream::getline(line, sizeof(line))) {
        return false;
    }
    string strLine(line);
    regex expression("([0-9.]+) ([\\S]+) ([\\S]+) \\[([ \\S]+)\\] \"([A-Z]+) ([\\S]+) ([^\\\"]+)\" ([0-9]+) ([0-9-]+) \"([^\"]+)\" \"([^\"]+)\"");

    string ipAddress = "";
    string userLogname = "";
    string authUser = "";
    string requestedDatetime = "";
    string httpMethod = "";
    string destinationUrl = "";
    string httpVersion = "";
    int statusCode = 0;
    long dataSize = 0;
    string referrerUrl = "";
    string userAgent = "";

    smatch match;
    if (!regex_search(strLine, match, expression) || match.size() != 12) {
        cerr << CouleurTTY(ROUGE) << "Failed to parse log line: " << strLine << CouleurTTY(RESET) << endl;
        return false;
    }

    ipAddress = match[1];
    userLogname = match[2];
    authUser = match[3];
    requestedDatetime = match[4];
    httpMethod = match[5];
    destinationUrl = match[6];
    httpVersion = match[7];
    statusCode = stoi(match[8]);
    if (match[9] == "-") {
        dataSize = 0;
    } else {
        dataSize = stol(match[9]);
    }
    referrerUrl = match[10];
    userAgent = match[11];

    size_t startPos = referrerUrl.find(baseUri);
    if (startPos != string::npos) {
        referrerUrl.replace(startPos, baseUri.length(), "");
    }

    entry = new LogEntry(ipAddress, userLogname, authUser, requestedDatetime,
                     httpMethod, destinationUrl, httpVersion,
                     statusCode, dataSize, referrerUrl, userAgent);

    return true;
} //----- Fin de getline

bool ApacheLogStream::fail() const
// Algorithme :
{
    return ifstream::fail();
} //----- Fin de fail

bool ApacheLogStream::eof() const
// Algorithme :
{
    return ifstream::eof();
} //----- Fin de eof

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

ApacheLogStream::ApacheLogStream(const string & filePath, const string & baseUri) : ifstream ( filePath ), baseUri ( baseUri )
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
