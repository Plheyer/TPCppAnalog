# Analog — Analyseur de logs Apache (Projet C++)

## 📌 Présentation du projet

**Analog** est un outil en ligne de commande permettant d’analyser des fichiers de logs Apache.

Il extrait des statistiques, filtre les hits selon plusieurs critères et peut générer un graphe de navigation au format GraphViz (.dot).

*Projet réalisé dans le cadre du TP C++ (Analyse de fichiers de log Apache).*

## 📂 Fonctionnalités principales

### ✔️ Extraction des statistiques

- Affichage des **10 documents les plus consultés**

### ✔️ Génération d’un graphe GraphViz

- `-g fichier.dot`

### ✔️ Filtrage des ressources externes

- `-e`

### ✔️ Filtrage temporel

- `-t heure`

## 🚀 Utilisation

### Syntaxe générale

./analog [options] fichier_log

### Options disponibles
| Option	| Description |
| --------- | ----------- |
| -g fichier.dot |	Génère un graphe au format GraphViz |
| -e |	Exclut les images / CSS / JS |
| -t heure |	Filtre les hits sur une heure donnée |
| (aucune option) |	Affiche le top 10 |

#### Exemples

##### ➡️ Générer un graphe

```sh
./analog -g sortie.dot access.log
```


##### ➡️ Filtrer les images et ne garder que l’heure 14

```sh
./analog -e -t 14 access.log
```


##### ➡️ Simple top 10

```sh
./analog access.log
```

## 🏗️ Config

Dans config.ini (ou tout autre fichier de configuration en format .ini), il faut définir :

- `debug` : un booléen indiquant si le mode débug est activé (true/false). False par défaut.
- `BASE_URI` : l'URI de base des requêtes des logs, un string. "" Par défaut.

## 🔧 Compilation

```sh
make
```

## 👥 Auteurs

- Corentin Lemaire
- Nicolas Colomb
- Nicolas Trehou

INSA Lyon — 2025

## 📜 Licence

Projet académique — réutilisation autorisée dans un contexte pédagogique.