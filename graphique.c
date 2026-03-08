#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <graph.h>
#include "graphique.h"

#define TOUCHE_GAUCHE 65361
#define TOUCHE_HAUT   65362
#define TOUCHE_DROITE 65363
#define TOUCHE_BAS    65364
#define TOUCHE_ENTER  65293
#define TOUCHE_ECHAP  65307

int _X, _Y; /* Variables globales de la souris */

static void dessiner_case(const Jeu *p, char *nom_img_hd, int i, int j) {
    int largeur_puzzle = p->colonnes * p->tile_w;
    int hauteur_puzzle = p->lignes * p->tile_h;
    int marge_x = (ECRAN_L - largeur_puzzle) / 2;
    int marge_y = (ECRAN_H - hauteur_puzzle) / 2;
    int num_tuile = p->grille[i][j];
    int x_ecran = marge_x + j * p->tile_w;
    int y_ecran = marge_y + i * p->tile_h;
    int col_origine, ligne_origine, xx, yy;

    if (num_tuile != 0) {
        col_origine = (num_tuile) % p->colonnes;
        ligne_origine = (num_tuile) / p->colonnes;
        
        xx = col_origine * p->tile_w;
        yy = ligne_origine * p->tile_h;
        ChargerImage(nom_img_hd, x_ecran, y_ecran, xx, yy, p->tile_w, p->tile_h);
    } else {
        ChoisirCouleurDessin(CouleurParNom("black"));
        RemplirRectangle(x_ecran, y_ecran, p->tile_w, p->tile_h);
        ChoisirCouleurDessin(CouleurParNom("white"));
        DessinerRectangle(x_ecran, y_ecran, p->tile_w, p->tile_h);
    }
}

static void afficher_infos(const Jeu *p) {
    char tampon[50];
    
    /* Nettoyage des zones de texte (fond blanc) */
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(10, ECRAN_H - 80, 360, 60);            
    RemplirRectangle(ECRAN_L - 330, ECRAN_H - 80, 320, 60); 

    /* Affichage des coups */
    ChoisirCouleurDessin(CouleurParNom("black"));
    sprintf(tampon, "Coups: %d", p->coups);
    EcrireTexte(20, ECRAN_H - 40, tampon, 2);

    /* --- DESSIN DU BOUTON QUITTER (Bas Droite) --- */
    DessinerRectangle(ECRAN_L - 310, ECRAN_H - 70, 280, 50);
    EcrireTexte(ECRAN_L - 300, ECRAN_H - 40, "QUITTER (Echap)", 1);
}

void dessiner_jeu(const Jeu *p, int id_image) {
    int i, j;
    char nom_img_hd[20];
    sprintf(nom_img_hd, "img%d.jpg", id_image);
    EffacerEcran(CouleurParNom("white"));
    for (i = 0; i < p->lignes; i++) {
        for (j = 0; j < p->colonnes; j++) {
            dessiner_case(p, nom_img_hd, i, j);
        }
    }
    afficher_infos(p);
}

void rafraichir_deplacement(const Jeu *p, int id_image, int lig_vide_avant, int col_vide_avant) {
    char nom_img_hd[20];
    sprintf(nom_img_hd, "img%d.jpg", id_image);
    dessiner_case(p, nom_img_hd, lig_vide_avant, col_vide_avant);
    dessiner_case(p, nom_img_hd, p->lig_vide, p->col_vide);
    afficher_infos(p);
}

int afficher_victoire(void) {
    int x_box = ECRAN_L / 2 - 200; 
    int y_box = ECRAN_H / 2 - 75;
    int x_btn_menu = x_box + 30;
    int x_btn_quit = x_box + 220;
    int y_btn = y_box + 90;
    int w_btn = 150;
    int h_btn = 40;
    int touche;
    
    ChoisirCouleurDessin(CouleurParNom("red"));
    RemplirRectangle(x_box, y_box, 400, 150);
    ChoisirCouleurDessin(CouleurParNom("black"));
    DessinerRectangle(x_box, y_box, 400, 150);
    
    ChoisirCouleurDessin(CouleurParNom("white"));
    EcrireTexte(x_box + 90, y_box + 40, "BRAVO ! GAGNE !", 2);
    
    RemplirRectangle(x_btn_menu, y_btn, w_btn, h_btn);
    RemplirRectangle(x_btn_quit, y_btn, w_btn, h_btn);
    
    ChoisirCouleurDessin(CouleurParNom("black"));
    DessinerRectangle(x_btn_menu, y_btn, w_btn, h_btn);
    EcrireTexte(x_btn_menu + 15, y_btn + 28, "MENU", 1);
    
    DessinerRectangle(x_btn_quit, y_btn, w_btn, h_btn);
    EcrireTexte(x_btn_quit + 10, y_btn + 28, "QUITTER", 1);
    
    while (1) {
        if (SourisCliquee()) {
            SourisPosition();
            if (_X >= x_btn_menu && _X <= x_btn_menu + w_btn &&
                _Y >= y_btn && _Y <= y_btn + h_btn) {
                return TOUCHE_ENTER;
            }
            if (_X >= x_btn_quit && _X <= x_btn_quit + w_btn &&
                _Y >= y_btn && _Y <= y_btn + h_btn) {
                return TOUCHE_ECHAP;
            }
        }
        if (ToucheEnAttente()) {
            touche = Touche();
            if (touche == TOUCHE_ENTER || touche == TOUCHE_ECHAP) return touche;
        }
    }
}

void dessiner_menu(Config *conf) {
    char buffer[100];
    int espace = (ECRAN_L - (3 * 300)) / 4; 
    int y_img = 150;
    int y_reglage = 550;

    EffacerEcran(CouleurParNom("white"));
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(ECRAN_L/2 - 150, 50, "CONFIGURATION DU TAQUIN", 2);
    EcrireTexte(ECRAN_L/2 - 350, 90, "1,2,3 : Choisir Image | Fleches : Taille | ENTREE : Jouer", 1);

    ChargerImage("ref1.jpg", espace + 50, y_img + 50, 0, 0, 200, 200);
    if (conf->image_choisie == 1) {
        ChoisirCouleurDessin(CouleurParNom("red"));
        DessinerRectangle(espace + 45, y_img + 45, 210, 210);
        DessinerRectangle(espace + 44, y_img + 44, 212, 212);
    }
    ChargerImage("ref2.jpg", espace*2 + 300 + 50, y_img + 50, 0, 0, 200, 200);
    if (conf->image_choisie == 2) {
        ChoisirCouleurDessin(CouleurParNom("red"));
        DessinerRectangle(espace*2 + 300 + 45, y_img + 45, 210, 210);
        DessinerRectangle(espace*2 + 300 + 44, y_img + 44, 212, 212);
    }
    ChargerImage("ref3.jpg", espace*3 + 600 + 50, y_img + 50, 0, 0, 200, 200);
    if (conf->image_choisie == 3) {
        ChoisirCouleurDessin(CouleurParNom("red"));
        DessinerRectangle(espace*3 + 600 + 45, y_img + 45, 210, 210);
        DessinerRectangle(espace*3 + 600 + 44, y_img + 44, 212, 212);
    }

    ChoisirCouleurDessin(CouleurParNom("black"));
    
    DessinerRectangle(ECRAN_L/2 - 200, y_reglage + 40, 40, 40);
    EcrireTexte(ECRAN_L/2 - 190, y_reglage + 70, "<", 2);
    sprintf(buffer, "LIGNES : %d", conf->nb_lignes);
    EcrireTexte(ECRAN_L/2 - 130, y_reglage + 70, buffer, 2);
    DessinerRectangle(ECRAN_L/2 + 50, y_reglage + 40, 40, 40);
    EcrireTexte(ECRAN_L/2 + 60, y_reglage + 70, ">", 2);

    DessinerRectangle(ECRAN_L/2 + 250, y_reglage + 40, 40, 40);
    EcrireTexte(ECRAN_L/2 + 260, y_reglage + 70, "v", 2);
    sprintf(buffer, "COLONNES : %d", conf->nb_cols);
    EcrireTexte(ECRAN_L/2 + 320, y_reglage + 70, buffer, 2);
    DessinerRectangle(ECRAN_L/2 + 520, y_reglage + 40, 40, 40);
    EcrireTexte(ECRAN_L/2 + 530, y_reglage + 70, "^", 2);
    
    ChoisirCouleurDessin(CouleurParNom("white")); 
    RemplirRectangle(ECRAN_L/2 - 100, 700, 200, 60); 
    ChoisirCouleurDessin(CouleurParNom("black"));
    DessinerRectangle(ECRAN_L/2 - 100, 700, 200, 60); 
    DessinerRectangle(ECRAN_L/2 - 101, 699, 202, 62);
    EcrireTexte(ECRAN_L/2 - 45, 740, "JOUER", 2); 
}

void gerer_menu(Config *conf) {
    int en_cours = 1;
    int touche, x, y, espace;
    int doit_dessiner = 1;
    int centre_x = ECRAN_L / 2;
    int y_reglage = 550;

    conf->image_choisie = 1; 
    conf->nb_lignes = 4; 
    conf->nb_cols = 4;

    while (en_cours) {
        if (doit_dessiner) {
            dessiner_menu(conf);
            doit_dessiner = 0;
        }
        
        if (SourisCliquee()) {
            SourisPosition();
            x = _X; y = _Y;
            espace = (ECRAN_L - 900) / 4;
            
            if (y >= 200 && y <= 400) {
                if (x >= espace + 50 && x <= espace + 250) { conf->image_choisie = 1; doit_dessiner = 1; }
                if (x >= espace*2 + 350 && x <= espace*2 + 550) { conf->image_choisie = 2; doit_dessiner = 1; }
                if (x >= espace*3 + 650 && x <= espace*3 + 850) { conf->image_choisie = 3; doit_dessiner = 1; }
            }
            if (y >= y_reglage + 40 && y <= y_reglage + 80) {
                if (x >= centre_x - 200 && x <= centre_x - 160 && conf->nb_lignes > 3) { conf->nb_lignes--; doit_dessiner = 1; }
                if (x >= centre_x + 50 && x <= centre_x + 90 && conf->nb_lignes < 8) { conf->nb_lignes++; doit_dessiner = 1; }
                if (x >= centre_x + 250 && x <= centre_x + 290 && conf->nb_cols > 3) { conf->nb_cols--; doit_dessiner = 1; }
                if (x >= centre_x + 520 && x <= centre_x + 560 && conf->nb_cols < 8) { conf->nb_cols++; doit_dessiner = 1; }
            }
            if (y >= 700 && y <= 760 && x >= ECRAN_L/2 - 100 && x <= ECRAN_L/2 + 100) {
                en_cours = 0;
            }
        }

        if (ToucheEnAttente()) {
            touche = Touche();
            if (touche == '1') { conf->image_choisie = 1; doit_dessiner = 1; }
            if (touche == '2') { conf->image_choisie = 2; doit_dessiner = 1; }
            if (touche == '3') { conf->image_choisie = 3; doit_dessiner = 1; }
            
            if (touche == TOUCHE_GAUCHE && conf->nb_lignes > 3) { conf->nb_lignes--; doit_dessiner = 1; }
            if (touche == TOUCHE_DROITE && conf->nb_lignes < 8) { conf->nb_lignes++; doit_dessiner = 1; }
            if (touche == TOUCHE_BAS && conf->nb_cols > 3) { conf->nb_cols--; doit_dessiner = 1; }
            if (touche == TOUCHE_HAUT && conf->nb_cols < 8) { conf->nb_cols++; doit_dessiner = 1; }
            
            if (touche == TOUCHE_ENTER) en_cours = 0; 
            if (touche == TOUCHE_ECHAP) exit(0); 
        }
        usleep(20000);
    }
}

int gerer_souris(Jeu *p) {
    int i_clic, j_clic, dx, dy;
    int largeur_puzzle = p->colonnes * p->tile_w;
    int hauteur_puzzle = p->lignes * p->tile_h;
    int marge_x = (ECRAN_L - largeur_puzzle) / 2;
    int marge_y = (ECRAN_H - hauteur_puzzle) / 2;
    int deplacement_effectue = 0;

    SourisPosition();

    /* --- DETECTION CLIC SUR BOUTON QUITTER --- */
    /* Coordonnées correspondant au rectangle dessiné dans afficher_infos */
    if (_X >= ECRAN_L - 310 && _X <= ECRAN_L - 30 &&
        _Y >= ECRAN_H - 70 && _Y <= ECRAN_H - 20) {
        return -1; /* Code pour dire "QUITTER" */
    }

    if (_X < marge_x || _Y < marge_y) return 0;

    j_clic = (_X - marge_x) / p->tile_w;
    i_clic = (_Y - marge_y) / p->tile_h;
    
    if (i_clic >= 0 && i_clic < p->lignes && j_clic >= 0 && j_clic < p->colonnes) {
        if (j_clic > p->col_vide) dx = j_clic - p->col_vide; 
        else dx = p->col_vide - j_clic;
        
        if (i_clic > p->lig_vide) dy = i_clic - p->lig_vide; 
        else dy = p->lig_vide - i_clic;
        
        if (dx + dy == 1) {
            if (dx == 1) { 
                if (j_clic < p->col_vide) deplacement_effectue = deplacer(p, 'g'); 
                else deplacement_effectue = deplacer(p, 'd'); 
            } else { 
                if (i_clic < p->lig_vide) deplacement_effectue = deplacer(p, 'h');
                else deplacement_effectue = deplacer(p, 'b');
            }
        }
    }
    return deplacement_effectue;
}