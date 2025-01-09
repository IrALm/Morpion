# Jeu de Morpion - Grille Infinie

## Description

Ce projet implémente le jeu de **Morpion** (Tic-Tac-Toe) avec une grille infinie, en **C++**, sans utiliser la programmation orientée objet (POO). L'objectif est d'utiliser des structures de données adaptées pour modéliser une grille infinie, permettant ainsi aux joueurs de jouer sans limite de taille de grille.

Le jeu simule 3 manches, et à la fin de chaque manche, les informations sont enregistrées dans un fichier `.txt`. Chaque sous-programme du jeu calcule également son temps d'exécution, dans le but de tester l'efficacité du programme.

### Fonctionnalités principales :
- **Grille infinie** : La grille est dynamique et peut s'étendre selon les besoins, permettant aux joueurs de jouer sur une grille de taille illimitée.
- **Sauvegarde des manches** : Les informations de chaque manche sont enregistrées dans un fichier `.txt` après chaque partie.
- **Mesure du temps d'exécution** : Le programme calcule le temps d'exécution pour chaque sous-programme (par exemple, la mise à jour de la grille, la vérification des conditions de victoire).
- **Simulations de 3 manches** : Le programme gère trois manches et sauvegarde les résultats dans des fichiers distincts pour chaque manche.

---

## Installation

### Prérequis

- **C++** (version 17 ou supérieure recommandée).
- Un compilateur **C++** comme `g++`.
- Aucun autre prérequis ni bibliothèque externe n'est nécessaire.

---

## Compilation et Exécution

Ce projet n'utilise pas de **Makefile** et n'a pas de dépendances externes. Voici comment compiler et exécuter le programme :

### 1. **Compilation**

Si vous utilisez **g++** pour compiler le projet, ouvrez un terminal dans le répertoire contenant le fichier source `morpion_projet.cpp` et exécutez la commande suivante pour compiler le programme :

```bash
g++ morpion_projet.cpp -o morpion_projet

pour l'execution :
```bash
./morpion_projet

