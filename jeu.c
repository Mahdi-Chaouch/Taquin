#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "jeu.h"

void initialiser_jeu(Jeu *p, int l, int c) {
    int numero = 1;
    int i, j;
    
    p->lignes = l;
    p->colonnes = c;
    p->coups = 0;

    /* --- FORCE LE VIDE EN HAUT A GAUCHE (0,0) --- */
    p->lig_vide = 0;
    p->col_vide = 0;

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            /* Si c'est la case (0,0), on met 0 (vide) */
            if (i == 0 && j == 0) {
                p->grille[i][j] = 0;
            } else {
                p->grille[i][j] = numero;
                numero++;
            }
        }
    }
}

int deplacer(Jeu *p, char direction) {
    int lig_cible = p->lig_vide;
    int col_cible = p->col_vide;

    /* On détermine quelle case va prendre la place du vide */
    /* Note : 'h' signifie que le vide va vers le haut (donc on échange avec la case du dessus) */
    if (direction == 'h') lig_cible--;      /* Haut */
    else if (direction == 'b') lig_cible++; /* Bas */
    else if (direction == 'g') col_cible--; /* Gauche */
    else if (direction == 'd') col_cible++; /* Droite */
    else return 0;

    /* Vérification des limites du tableau */
    if (lig_cible < 0 || lig_cible >= p->lignes || 
        col_cible < 0 || col_cible >= p->colonnes) return 0;

    /* Echange des valeurs */
    p->grille[p->lig_vide][p->col_vide] = p->grille[lig_cible][col_cible];
    p->grille[lig_cible][col_cible] = 0;
    
    /* Mise à jour de la position du vide */
    p->lig_vide = lig_cible;
    p->col_vide = col_cible;
    p->coups++;
    return 1;
}

void melanger_jeu(Jeu *p, int n) {
    int i, mouvement;
    
    /* 1. On effectue n mouvements aléatoires pour briser l'ordre */
    for (i = 0; i < n; i++) {
        mouvement = rand() % 4;
        switch (mouvement) {
            case 0: deplacer(p, 'h'); break;
            case 1: deplacer(p, 'b'); break;
            case 2: deplacer(p, 'g'); break;
            case 3: deplacer(p, 'd'); break;
        }
    }

    /* 2. MODIFICATION : On ramène le vide en (0,0) par des déplacements légaux.
       Cela permet de garder la solubilité du puzzle (parité des permutations). 
       Si on forçait juste p->grille[0][0]=0 sans déplacer, le jeu pourrait être impossible. */

    /* Tant que le vide n'est pas sur la colonne 0, on le déplace à gauche */
    while (p->col_vide > 0) {
        deplacer(p, 'g');
    }

    /* Tant que le vide n'est pas sur la ligne 0, on le déplace vers le haut */
    while (p->lig_vide > 0) {
        deplacer(p, 'h');
    }

    /* 3. On remet le compteur à 0 car ces mouvements font partie de l'initialisation */
    p->coups = 0; 
}

int verifier_victoire(const Jeu *p) {
    int i, j;
    int attendu = 1;
    
    for (i = 0; i < p->lignes; i++) {
        for (j = 0; j < p->colonnes; j++) {
            
            /* Cas particulier : Case (0,0) doit être vide (0) */
            if (i == 0 && j == 0) {
                if (p->grille[i][j] != 0) return 0;
            } 
            else {
                /* Les autres doivent être 1, 2, 3... */
                if (p->grille[i][j] != attendu) return 0;
                attendu++;
            }
        }
    }
    return 1; /* Victoire ! */
}