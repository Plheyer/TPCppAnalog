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
//----------------------------------------------------- Attributs publics
    string ip_address;
    int timestamp;
    string http_method;
    int status_code;
    long data_size;
    string referrer_url;
    string user_agent;

//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    LogEntry ( ){
    #ifdef MAP
        cout << "Appel au constructeur de <LogEntry>" << endl;
    #endif
    }
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~LogEntry ( ){
    #ifdef MAP
        cout << "Appel au destructeur de <LogEntry>" << endl;
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

//-------------------------------- Autres définitions dépendantes de <LogEntry>

#endif //TPCPPANALOG_LOGENTRY_H

