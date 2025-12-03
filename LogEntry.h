/*************************************************************************
                           LogEntry  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <LogEntry> (fichier LogEntry.h) ----------------

#ifndef TPCPPANALOG_LOGENTRY_H
#define TPCPPANALOG_LOGENTRY_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <LogEntry>
//
//
//------------------------------------------------------------------------

class LogEntry
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    const string GetIpAddress() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const int GetTimestamp() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const string GetHttpMethod() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const int GetStatusCode() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const long GetDataSize() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const string GetReferrerUrl() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    const string GetUserAgent() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    LogEntry (string ipAddress = "",
              int timestamp = 0,
              string httpMethod = "",
              int statusCode = 0,
              long dataSize = 0,
              string referrerUrl = "",
              string userAgent = "" );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogEntry ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const string ipAddress;
    const int timestamp;
    const string httpMethod;
    const int statusCode;
    const long dataSize;
    const string referrerUrl;
    const string userAgent;

};

//-------------------------------- Autres définitions dépendantes de <LogEntry>

#endif //TPCPPANALOG_LOGENTRY_H

