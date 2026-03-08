#ifndef JEU_H
#define JEU_H

#define MAX_SIZE 8

typedef struct {
    int lignes;
    int colonnes;
    int grille[MAX_SIZE][MAX_SIZE];
    int lig_vide;
    int col_vide;
    int coups;
    int tile_w;
    int tile_h;
} Jeu;

void initialiser_jeu(Jeu *p, int l, int c);
int deplacer(Jeu *p, char direction);
void melanger_jeu(Jeu *p, int n);
int verifier_victoire(const Jeu *p);

#endif