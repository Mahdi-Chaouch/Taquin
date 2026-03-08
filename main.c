#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 700
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <graph.h>
#include "jeu.h"
#include "graphique.h"

#define TOUCHE_GAUCHE 65361
#define TOUCHE_HAUT   65362
#define TOUCHE_DROITE 65363
#define TOUCHE_BAS    65364
#define TOUCHE_ECHAP  65307
#define TOUCHE_ENTER  65293

const int LARGEURS_IMAGES[4] = {0, 1000, 1000, 1000};
const int HAUTEURS_IMAGES[4] = {0, 1000, 1000, 1000};

int main(void) {
    Jeu ma_partie;
    Config configuration;
    int touche;
    int doit_dessiner;
    int lig_avant, col_avant, a_bouge;
    int application_en_cours = 1; 
    int choix_fin;
    int retour_souris;

    srand(time(NULL));

    InitialiserGraphique();
    CreerFenetre(0, 0, ECRAN_L, ECRAN_H); 

    while (application_en_cours) {
        doit_dessiner = 1;
        gerer_menu(&configuration);

        initialiser_jeu(&ma_partie, configuration.nb_lignes, configuration.nb_cols);
        ma_partie.tile_w = LARGEURS_IMAGES[configuration.image_choisie] / configuration.nb_cols;
        ma_partie.tile_h = HAUTEURS_IMAGES[configuration.image_choisie] / configuration.nb_lignes;
        
        if (ma_partie.tile_w < 1) ma_partie.tile_w = 1;
        if (ma_partie.tile_h < 1) ma_partie.tile_h = 1;
        
        melanger_jeu(&ma_partie, 500);
        EffacerEcran(CouleurParNom("white"));

        while (1) {
            if (doit_dessiner) {
                dessiner_jeu(&ma_partie, configuration.image_choisie);
                doit_dessiner = 0;
            }
            
            if (SourisCliquee()) {
                lig_avant = ma_partie.lig_vide;
                col_avant = ma_partie.col_vide;
                
                retour_souris = gerer_souris(&ma_partie);

                /* Si retour_souris == -1, c'est le bouton QUITTER */
                if (retour_souris == -1) {
                    application_en_cours = 0;
                    break;
                }
                /* Si retour_souris == 1, c'est un déplacement valide */
                else if (retour_souris == 1) {
                    rafraichir_deplacement(&ma_partie, configuration.image_choisie, lig_avant, col_avant);
                    if (verifier_victoire(&ma_partie)) { 
                        dessiner_jeu(&ma_partie, configuration.image_choisie); 
                        choix_fin = afficher_victoire(); 
                        if (choix_fin == TOUCHE_ECHAP) application_en_cours = 0;
                        break; 
                    }
                }
            }
            
            if (ToucheEnAttente()) {
                touche = Touche();
                if (touche == TOUCHE_ECHAP) {
                    application_en_cours = 0;
                    break;
                }
                if (touche == TOUCHE_GAUCHE || touche == TOUCHE_DROITE || touche == TOUCHE_HAUT || touche == TOUCHE_BAS) {
                    lig_avant = ma_partie.lig_vide;
                    col_avant = ma_partie.col_vide;
                    a_bouge = 0;
                    if (touche == TOUCHE_GAUCHE) a_bouge = deplacer(&ma_partie, 'g');
                    else if (touche == TOUCHE_DROITE) a_bouge = deplacer(&ma_partie, 'd');
                    else if (touche == TOUCHE_HAUT)   a_bouge = deplacer(&ma_partie, 'h');
                    else if (touche == TOUCHE_BAS)    a_bouge = deplacer(&ma_partie, 'b');
                    
                    if (a_bouge) rafraichir_deplacement(&ma_partie, configuration.image_choisie, lig_avant, col_avant);
                }
                if (verifier_victoire(&ma_partie)) { 
                    dessiner_jeu(&ma_partie, configuration.image_choisie); 
                    choix_fin = afficher_victoire();
                    if (choix_fin == TOUCHE_ECHAP) application_en_cours = 0;
                    break; 
                }
            }
            usleep(20000);
        }
    }
    FermerGraphique();
    return EXIT_SUCCESS;
}