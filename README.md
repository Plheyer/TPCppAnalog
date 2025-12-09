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

./bin/analog [options] fichier_log

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
./bin/analog -g sortie.dot access.log
```


##### ➡️ Exclure les images/CSS/JS et ne garder que l’heure 14

```sh
./bin/analog -e -t 14 access.log
```


##### ➡️ Simple top 10

```sh
./bin/analog access.log
```

## 🏗️ Config

Dans config.ini (ou tout autre fichier de configuration en format .ini), il faut définir :

- `debug` : un booléen indiquant si le mode débug est activé (true/false). False par défaut.
- `BASE_URI` : l'URI de base des requêtes des logs, un string. "" Par défaut.

## 🔧 Compilation

```sh
make
```

## ❌ Erreurs courantes

- **Erreur: Impossible d'ouvrir le fichier ...  pour la lecture.** : Vérifiez que le fichier de log existe et que vous avez la permission de lire ce dernier.
- **Failed to parse log line: ...** : Vérifiez que le fichier de log que vous avez fourni est bien un fichier de log au format Apache standard.
- **Error: Could not open config file: ...** : Vérifiez que le fichier de configuration (.ini) existe dans le même répertoire de l'exécutable et que vous avez la permission de lire ce dernier.
- **Erreur: Impossible d'ouvrir le fichier ... pour l'écriture.** : Vérifiez que vous avez les droits d'écriture dans le répertoire de destination pour votre fichier GraphViz (ce que vous avez indiqué après l'option -g).
- **Erreur lors de la génération du fichier GraphViz** : Vérifiez que vous avez les droits d'écriture dans le répertoire de destination pour votre fichier GraphViz (ce que vous avez indiqué après l'option -g).

## 👥 Auteurs

- Corentin Lemaire
- Nicolas Colomb
- Nicolas Trehou

INSA Lyon — 2025

## 📜 Licence

Projet académique — réutilisation autorisée dans un contexte pédagogique.