/*************************************************************************
                           CouleurTTY  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <CouleurTTY> (fichier CouleurTTY.h) ----------------

#ifndef TPCPPANALOG_COULEURTTY_H
#define TPCPPANALOG_COULEURTTY_H

//--------------------------------------------------- Interfaces utilisées
#include <cstring>
#include <iostream>
using namespace std;
//------------------------------------------------------------- Constantes
static const char * const COULEUR [ ] = {
    "\033[30m", /* Noir */ "\033[31m", /* Rouge */ "\033[32m", /* Vert */
    "\033[33m", /* Jaune */ "\033[34m", /* Bleu */ "\033[35m", /* Magenta */
    "\033[36m", /* Cyan */ "\033[37m", /* Blanc */ "\033[m\017" /* Reset */ };
//------------------------------------------------------------------ Types
enum IndexCouleur { NOIR, ROUGE, VERT, JAUNE, BLEU, MAGENTA, CYAN, BLANC, RESET };
//------------------------------------------------------------------------
// Rôle de la classe <CouleurTTY>
// Classe manipulateur pour afficher du texte coloré dans un terminal TTY
// en utilisant les codes ANSI escape.
//------------------------------------------------------------------------
class CouleurTTY
{
//----------------------------------------------------------------- PUBLIC
public:
//----------------------------------------------------- Méthodes publiques
    inline friend ostream & operator << ( ostream & os, const CouleurTTY & manip )
    {
        os.write ( COULEUR [ manip.index ], strlen ( COULEUR [ manip.index ] ) );
        return os.flush ( ) ;
    }
    // Mode d'emploi :
    // Surcharge de l'opérateur << pour permettre l'utilisation de CouleurTTY
    // comme manipulateur de flux avec cout.
    // Exemple : cout << CouleurTTY(ROUGE) << "texte rouge" << CouleurTTY(RESET);
    // Contrat :
    // L'index de couleur doit être valide (membre de l'énumération IndexCouleur)
//-------------------------------------------- Constructeurs - destructeur
    explicit CouleurTTY ( IndexCouleur i ) : index ( i ) { }
    // Mode d'emploi :
    // Constructeur qui initialise l'objet avec un index de couleur.
    // Le constructeur est explicite pour éviter les conversions implicites.
    // Contrat :
    // L'index de couleur doit être un membre valide de l'énumération IndexCouleur
//------------------------------------------------------------------ PRIVE
private:
//----------------------------------------------------- Attributs privés
    IndexCouleur index;
};

//-------------------------------- Autres définitions dépendantes de <CouleurTTY>

#endif //TPCPPANALOG_COULEURTTY_H

