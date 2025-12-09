/*************************************************************************
                           Config  -  Gère la configuration du programme
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Config> (fichier Config.h) ----------------

#ifndef TPCPPANALOG_CONFIG_H
#define TPCPPANALOG_CONFIG_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Config>
// Classe chargeant la configuration du fichier config.ini
//------------------------------------------------------------------------
class Config
{
//----------------------------------------------------------------- PUBLIC
public:
    bool debug;
    string baseUri;
//----------------------------------------------------- Méthodes publiques
    bool LoadFromFile(const string& filename = "config.ini");
    // Mode d'emploi :
    //    Charge la configuration à partir du fichier donné.
    //    Le fichier doit respecter un format clé=valeur.
    //    La valeur par défaut est "config.ini"
    // Retour :
    //    true si le chargement a réussi, false sinon.
//-------------------------------------------- Constructeurs - destructeur
    explicit Config(): debug(false), baseUri("") { }
    // Mode d'emploi :
    // Constructeur qui initialise l'objet.
    // Le constructeur est explicite pour éviter les conversions implicites.
    // Contrat :
    //
//------------------------------------------------------------------ PRIVE
private:
    string trim(const string& str);
//----------------------------------------------------- Attributs privés
};

//-------------------------------- Autres définitions dépendantes de <Config>

#endif //TPCPPANALOG_CONFIG_H

