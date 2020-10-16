#ifndef __PROMO__
#define __PROMO__

#include <stdio.h>
#include <time.h>
#include <string.h>

#define TAILLE_MAX_NOM 20
#define TAILLE_MAX_PROMO 100
#define FICHIER_PROMO "promotions.txt"
#define FICHIER_ETUDIANTS "etudiant.dat"

typedef enum{
	Masculin,
	Feminin
}t_genre;

typedef struct{
	int jour;
	int mois;
	int an;
}t_date;

typedef enum{
	Non,
	Oui
}actif, verification;

//	c)
typedef struct{
	char nom[TAILLE_MAX_NOM];
	char prenom[TAILLE_MAX_NOM];
	t_date dNaissance;
	t_genre genre;
	int promo;
}t_etudiant;

//	f)
typedef struct{
	int taillePromo;
	int promo;
	t_etudiant gEtudiant[TAILLE_MAX_PROMO];
}t_promo;

// d)
void saisis_etudiant(t_etudiant *etudiant, int p, FILE *fic);
// e)
void affiche_etudiant(t_etudiant etudiant);
// g)
void saisis_promotion(t_promo *promo, int p, FILE *fic);
// h)
void affiche_promotion(t_promo promo);
// i)
t_promo initialise_promotion();
// j)
void cherche_homonymes(t_promo p, char *nom);
// k)
void cherche_prefixe(t_promo p, t_promo *res, char *prefixe);


/***************************************************************************/
void affiche_liste_promotion();
void getAll(char *nom, FILE *fic, int opt);
/***************************************************************************/
t_date saisis_dNaissance();
void affiche_result_recherche(t_promo *p1, int *i);
//void affiche_mois_fr(int mois);

#endif
