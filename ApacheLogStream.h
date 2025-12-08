/*************************************************************************
                ApacheLogStream  - Gère la lecture d'un flux de logs Apache
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <ApacheLogStream> (fichier ApacheLogStream.h) ----------------
#if ! defined ( APACHE_LOG_STREAM_H )
#define APACHE_LOG_STREAM_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
using namespace std;

#include "LogEntry.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ApacheLogStream>
//  Gère la lecture d'un flux de logs Apache
//
//------------------------------------------------------------------------

class ApacheLogStream : ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    /**
     * Lit une ligne du flux de logs Apache et la retourne sous forme d'un LogEntry
     * @return L'entrée de log lue
     */
    LogEntry getline();

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    /**
     * Constructeur par défaut
     */
    ApacheLogStream ( const string & filePath, const string & baseUri = "" );

    /**
     * Destructeur, libérant la mémoire de la liste
     */
    virtual ~ApacheLogStream ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    const string baseUri;
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // APACHE_LOG_STREAM_H

