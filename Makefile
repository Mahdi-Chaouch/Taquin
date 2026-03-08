# --- Définitions des variables ---
CC = gcc
# Ajout de -Wall pour voir les avertissements (très important pour debug)
CFLAGS = -ansi -pedantic -Wall
EXE = taquin
OFILES = main.o jeu.o graphique.o

# Chemins vers la libgraph (A vérifier sur ton PC WSL !)
INCLUDES = -I$(HOME)/BIBLI/libgraph/include
LIBS = -L$(HOME)/BIBLI/libgraph/lib -lgraph -lX11
RPATH = -Wl,-rpath=$(HOME)/BIBLI/libgraph/lib

# --- Règle par défaut ---
but : ${EXE}

# --- Édition de liens (Création de l'exécutable) ---
${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES} $(LIBS) $(RPATH)

# --- Compilation séparée ---
main.o : main.c jeu.h graphique.h
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

# jeu.c n'utilise pas la libgraph, donc pas besoin de $(INCLUDES) ici
jeu.o : jeu.c jeu.h
	$(CC) $(CFLAGS) -c jeu.c

graphique.o : graphique.c graphique.h jeu.h
	$(CC) $(CFLAGS) $(INCLUDES) -c graphique.c

# --- Commandes utilitaires ---
run : ${EXE}
	./${EXE}

clean :
	rm -f ${OFILES} ${EXE}

.PHONY : run clean but
