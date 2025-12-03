/*************************************************************************
                           LogEntry  -  description
                             -------------------
    début                : 03-12-2025
    copyright            : (C) 2025 par Corentin LEMAIRE | Nicolas COLOMB | Nicolas TREHOU
    e-mail               : corentin.lemaire@insa-lyon.fr | nicolas.colomb@insa-lyon.fr | nicolas.trehou@insa-lyon.fr
*************************************************************************/

#include <limits>
#include <iostream>
#include <cstring>
#include "./CouleurTTY.h"
using namespace std;
#define MAX_TAMPON 100

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fonction pour lire un entier de manière sécurisée
bool lireEntier(int& valeur) {
    if (cin >> valeur) {
        clearInputBuffer();
        return true;
    } else {
        clearInputBuffer();
        return false;
    }
}

// Fonction pour lire un caractère de manière sécurisée
bool lireCaractere(char& valeur) {
    if (cin >> valeur) {
        clearInputBuffer();
        return true;
    } else {
        clearInputBuffer();
        return false;
    }
}

// Fonction pour lire une chaîne de caractères de manière sécurisée
bool lireChaine(char* chaine, int taille) {
    if (cin >> chaine) {
        clearInputBuffer();
        return true;
    } else {
        clearInputBuffer();
        return false;
    }
}

// Fonction pour lire une string de manière sécurisée
bool lireString(string& str) {
    if (cin >> str) {
        clearInputBuffer();
        return true;
    } else {
        clearInputBuffer();
        return false;
    }
}

int main()
{
    cout << CouleurTTY ( BLEU ) << "BLEU " << CouleurTTY ( ROUGE ) << "ROUGE "
        << CouleurTTY ( VERT ) << "VERT" << CouleurTTY ( RESET ) << endl;
    return 0;
}