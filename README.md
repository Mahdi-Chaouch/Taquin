Taquin

Taquin est un jeu graphique développé en langage C (ANSI C89) dans le cadre de la SAE 1.1 « Implémentation d’un jeu vidéo » du BUT Informatique.

Le projet propose une version numérique du jeu du taquin : une image est découpée en plusieurs tuiles, mélangée, puis le joueur doit reconstituer l’image originale en faisant glisser les cases vers l’espace vide.

Ce projet utilise la bibliothèque graphique fournie par l’IUT. Il ne peut donc pas être compilé directement sur n’importe quelle machine sans cette bibliothèque et ses dépendances.

Objectif du projet

L’objectif de ce projet était de concevoir un jeu complet en respectant plusieurs contraintes pédagogiques :

développement en C89

organisation modulaire du code en plusieurs fichiers .c et .h

compilation à l’aide d’un Makefile

utilisation d’une bibliothèque graphique fournie par l’IUT

implémentation d’une logique de jeu fiable garantissant que les puzzles générés soient toujours solvables

Fonctionnalités

Le jeu comporte trois écrans principaux.

Menu de configuration

Avant de lancer une partie, le joueur peut :

choisir une image parmi plusieurs propositions

sélectionner la taille de la grille

définir le nombre de lignes et de colonnes entre 3 et 8

lancer la partie avec un bouton « jouer »

Écran de jeu

Une fois la partie lancée :

la fenêtre s’adapte automatiquement à la taille de la grille

l’image choisie est découpée en tuiles mélangées

une case noire représente l’espace vide

une miniature de l’image originale reste affichée comme référence

un compteur de coups est affiché et mis à jour en temps réel

Écran de victoire

Lorsque toutes les tuiles sont remises dans l’ordre, le programme détecte automatiquement la victoire et affiche un message de félicitations.

Contrôles

Le jeu est jouable à la fois à la souris et au clavier.

Souris

Dans le menu, la souris permet de sélectionner l’image, modifier la taille de la grille et lancer la partie.

Pendant la partie, un clic sur une tuile adjacente à la case vide permet de déplacer cette tuile.

Clavier

Dans le menu :

les touches 1, 2 et 3 permettent de choisir l’image

les flèches directionnelles permettent de modifier la taille de la grille

la touche Entrée lance la partie

Pendant la partie :

les flèches directionnelles permettent de déplacer la case vide

À tout moment :

la touche Échap permet de quitter le programme

Technologies utilisées

langage : C (ANSI C89)

bibliothèque graphique : bibliothèque fournie par l’IUT

compilation : Makefile

environnement visé : Linux avec X11

Structure du projet

Le projet est organisé de manière modulaire.

Taquin
main.c : point d’entrée du programme et gestion générale de l’exécution
jeu.c / jeu.h : logique du jeu et manipulation de la grille
graphique.c / graphique.h : affichage graphique et gestion des interactions
Makefile : automatisation de la compilation
images : ressources graphiques utilisées pour le puzzle

Logique du jeu

La logique du jeu repose sur une structure principale qui stocke notamment :

le nombre de lignes et de colonnes de la grille

l’état de la grille du puzzle

la position de la case vide

le nombre de coups joués

les dimensions graphiques des tuiles

Une structure de configuration est également utilisée pour mémoriser les paramètres choisis par le joueur dans le menu avant l’initialisation de la partie.

Mélange et solvabilité

Pour garantir que chaque puzzle puisse être résolu, le mélange n’est pas effectué de manière totalement aléatoire.

Le programme commence par créer une grille déjà résolue. Ensuite, il effectue un grand nombre de déplacements valides aléatoires de la case vide. Cette méthode garantit que la configuration finale est atteignable à partir de la solution.

Boucle principale

Le jeu fonctionne grâce à une boucle principale qui réalise en continu :

l’affichage de l’état courant du jeu

la lecture des entrées clavier et souris

la mise à jour de la logique du jeu

la vérification de la condition de victoire

une temporisation permettant d’assurer une exécution fluide

Le programme optimise également l’affichage en évitant de redessiner l’écran lorsque rien n’a changé.

Compilation

La compilation du projet est réalisée à l’aide du Makefile fourni dans le repository.

Les commandes principales permettent de compiler le programme, d’exécuter le jeu et de nettoyer les fichiers générés lors de la compilation.

La compilation dépend de la bibliothèque graphique fournie par l’IUT ainsi que des bibliothèques nécessaires à l’environnement graphique X11.

Contexte pédagogique

Ce projet a été réalisé en binôme dans le cadre de la SAE 1.1 du BUT Informatique.

Il a permis de travailler :

la programmation en langage C

la conception et l’utilisation de structures de données

l’organisation modulaire d’un projet logiciel

l’utilisation d’un Makefile

la gestion d’une interface graphique

le travail collaboratif sur un projet informatique

Auteurs

Mahdi Chaouch
Rayan Ishac Belabed

Projet réalisé dans le cadre du BUT Informatique.
