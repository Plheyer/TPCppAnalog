/*************************************************************************
                           LogEntry  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <LogEntry> (fichier LogEntry.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const string LogEntry::GetIpAddress() const
// Algorithme :
{
    return ipAddress;
} //----- Fin de GetIpAddress

const int LogEntry::GetTimestamp() const
// Algorithme :
{
    return timestamp;
} //----- Fin de GetTimestamp

const string LogEntry::GetHttpMethod() const
// Algorithme :
{
    return httpMethod;
} //----- Fin de GetHttpMethod

const int LogEntry::GetStatusCode() const
// Algorithme :
{
    return statusCode;
} //----- Fin de GetStatusCode

const long LogEntry::GetDataSize() const
// Algorithme :
{
    return dataSize;
} //----- Fin de GetDataSize

const string LogEntry::GetReferrerUrl() const
// Algorithme :
{
    return referrerUrl;
} //----- Fin de GetReferrerUrl

const string LogEntry::GetUserAgent() const
// Algorithme :
{
    return userAgent;
} //----- Fin de GetUserAgent

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

LogEntry::LogEntry(
    string ipAddress,
    int timestamp,
    string httpMethod,
    int statusCode,
    long dataSize,
    string referrerUrl,
    string userAgent) : ipAddress(ipAddress), timestamp(timestamp), httpMethod(httpMethod),
      statusCode(statusCode), dataSize(dataSize), referrerUrl(referrerUrl),
      userAgent(userAgent) {
#ifdef MAP
    cout << "Appel au constructeur de <LogEntry>" << endl;
#endif
} //----- Fin de LogEntry


LogEntry::~LogEntry ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <LogEntry>" << endl;
#endif
} //----- Fin de ~LogEntry


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
