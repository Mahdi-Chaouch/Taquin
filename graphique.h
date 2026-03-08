#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include "jeu.h"

#define ECRAN_L 1920
#define ECRAN_H 1080

typedef struct {
    int image_choisie;
    int nb_lignes;
    int nb_cols;
} Config;

void dessiner_jeu(const Jeu *p, int id_image);
void rafraichir_deplacement(const Jeu *p, int id_image, int lig_vide_avant, int col_vide_avant);
int afficher_victoire(void);
void gerer_menu(Config *conf);
int gerer_souris(Jeu *p);

#endif