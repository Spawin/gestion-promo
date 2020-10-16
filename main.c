#include <stdio.h>
#include <stdlib.h>
#include "promotion.h"

void affichage_menu(int promo);
void msgMauvaisChoix();
void problemeFichier(char *nomFichier);

int main(int argc, char** argv){
	char rep, motRecherche[TAILLE_MAX_NOM];
	int opt = 0, promo = 0, i; 
	t_etudiant etudiant;
	t_promo maPromo;
	FILE *ficLE, *fic;
	
	if ((ficLE=fopen(FICHIER_ETUDIANTS,"ab+"))==NULL)
	{
		problemeFichier(FICHIER_ETUDIANTS);
		exit(EXIT_FAILURE);
	}
	
	printf("\t\t === Bienvenue sur le programme de gestion des promotions ===");
	
	affichage_menu(promo);
	
	do{
		scanf("%d", &opt);
		fflush(stdin);
		
		switch(opt){
			case 1:// Afficher les promotions disponibles
				if(promo != 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				affiche_liste_promotion();
				
				affichage_menu(promo);
				break;
				
			case 2:// Chercher des homonymes dans les noms des étudiants de toutes les promotions
				if(promo != 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("Entrez le nom : ");
				scanf("%s", &motRecherche);
				fflush(stdin);
				
				getAll(motRecherche, ficLE, opt);
				
				affichage_menu(promo);
				break;
				
			case 3:// Chercher avec un préfixe dans les noms des étudiants de toutes les promotions
				if(promo != 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("Entrez le pr%cfixe : ", -126);
				scanf("%s", &motRecherche);
				fflush(stdin);
				
				getAll(motRecherche, ficLE, opt);
				
				affichage_menu(promo);
				
				break;
				
			case 4:// Ajouter une promotion
				if(promo != 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("\nVeuillez entrer la promotion (l'ann%ce) : ", -126);
				scanf("%d", &promo);
				fflush(stdin);
				
				if ((fic = fopen(FICHIER_PROMO,"a+")) == NULL)
				{
					problemeFichier(FICHIER_PROMO);
					promo = 0;
				}
				else{
					int p = 0;
					while(!feof(fic)){
						fscanf(fic, "%d\n", &p);
						if(promo == p){
							printf("\nCette promotion existe d%cj%c !\n", -126, -123);
							promo = 0;
							break;
						}
					}
					if(promo != 0){
						p = 0;
						i = 100;//pour vérifier le passage dans la boucle
						rewind(fic);
						verification deja = Non;
						FILE *prov = fopen("prov", "w");
						if(prov == NULL)
							exit(EXIT_FAILURE);
							
						while(!feof(fic)){
							fscanf(fic, "%d\n", &p);
							if(promo < p && deja == Non && promo!=0){
								fprintf(prov, "%d\n", promo);
								deja = Oui;
							}
							if(p!=0)
								fprintf(prov, "%d\n", p);
						}
						if(promo > p){
							fprintf(prov, "%d\n", promo);
						}
						fclose(prov);
						
						saisis_promotion(&maPromo, promo, ficLE);
						printf("\n\tPromotion en cours : %d\n", promo);
						affiche_promotion(maPromo);
					}
					fclose(fic);
					if(i == 100){
						remove(FICHIER_PROMO);
						rename("prov", FICHIER_PROMO);
					}
				}
				
				affichage_menu(promo);
				break;
				
			case 5:// Editer ou afficher une promotion
				if(promo != 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				printf(" Entrez la promotion : ");
				scanf("%d", &promo);
				fflush(stdin);
				
				verification existeL = Non;
				if ((fic = fopen(FICHIER_PROMO,"r")) == NULL)
				{
					problemeFichier(FICHIER_PROMO);
					promo = 0;
				}
				else
				{
					int p;
					while(!feof(fic))
					{
						fscanf(fic, "%d\n", &p);
						if(promo == p){
							existeL = Oui;
							// on va récupérer les étudiants de cette promo
							i = 0;
							rewind(ficLE);
							while(!feof(ficLE)){
								fread(&etudiant, sizeof(t_etudiant), 1, ficLE);
								if(etudiant.promo == promo){
									maPromo.gEtudiant[i++] = etudiant;
								}
								memset(&etudiant, 0, sizeof(etudiant));
							}
							if(i != 0){
								maPromo.taillePromo = i;
								maPromo.promo = promo;
							}
							//
							affiche_promotion(maPromo);
							break;
						}
					}
					fclose(fic);
				}
				if(existeL == Non){
					promo = 0;
					printf("\nPas de donn%ces sur cette promotion !", -126);
				}
				
				affichage_menu(promo);
				
				break;
				
			case 6:// Afficher la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("    Nombre d'%ctudiant dans cette promotion : %d\n", -126, maPromo.taillePromo);
				affiche_promotion(maPromo);
				
				affichage_menu(promo);
				
				break;
				
			case 7:// Afficher un étudiant de la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("\n\tNum%cro de l'%ctudiant (commence de 0) : ", -126, -126);
				scanf("%d", &i);
				fflush(stdin);
				
				if(i >= maPromo.taillePromo){
					printf("\n\n   Ce num%cro ne correspond %c aucun %ctudiant\n", -126, -123, -126);
					affichage_menu(promo);
					break;
				}
				
				affiche_etudiant(maPromo.gEtudiant[i]);
				
				affichage_menu(promo);
				break;
				
			case 8:// Chercher des homonymes dans les noms des étudiants de la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				printf("Entrez le nom : ");
				scanf("%s", &motRecherche);
				fflush(stdin);
				
				cherche_homonymes(maPromo, motRecherche);
				
				affichage_menu(promo);
				break;
				
			case 9:// Chercher avec un préfixe dans les noms des étudiants de la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				t_promo pProv;
				printf("Entrez le pr%cfixe : ", -126);
				scanf("%s", &motRecherche);
				fflush(stdin);
				cherche_prefixe(maPromo, &pProv, motRecherche);
				affiche_promotion(pProv);
				
				affichage_menu(promo);
				break;
				
			case 10:// Ajouter un étudiant à la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				if(maPromo.taillePromo == TAILLE_MAX_PROMO){
					printf("\n\t\t!!! TAILLE MAXIMALE DE LA PROMOTION ATTEINTE !!!");
					break;
				}
				
				printf("-- Etudiant n.%d --", maPromo.taillePromo);
				saisis_etudiant(&etudiant, promo, ficLE);
				maPromo.gEtudiant[maPromo.taillePromo] = etudiant;
				maPromo.taillePromo++;
				
				affichage_menu(promo);
				break;
				
			case 11:// Supprimer un étudiant de la promotion en cours
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				i = -1;
				printf("\n\tNum%cro de l'%ctudiant (commence de 0) : ", -126, -126);
				scanf("%d", &i);
				fflush(stdin);
				
				if(i >= maPromo.taillePromo){
					printf("\n\n   Ce num%cro ne correspond %c aucun %ctudiant\n", -126, -123, -126);
					affichage_menu(promo);
					break;
				}
				
				printf("Voulez-vous suprimer l'%ctudiant %s %s ? ( O / N ) : ", -126, maPromo.gEtudiant[i].prenom, maPromo.gEtudiant[i].nom);
				scanf("%c", &rep);
				fflush(stdin);
				if(rep == 'O' || rep == 'o'){
					if ((fic = fopen("prov", "ab+")) == NULL){
						printf("Impossible de cr%cer le fichier provisoire", -126);
						exit(EXIT_FAILURE);
					}
					else{
						rewind(ficLE);
						t_promo p;
						int j = 0;
						while(!feof(ficLE)){
							fread(&etudiant, sizeof(t_etudiant), 1, ficLE);
							if(strcmp(etudiant.nom, maPromo.gEtudiant[i].nom) == 0 && strcmp(etudiant.prenom, maPromo.gEtudiant[i].prenom) == 0){
								memset(&etudiant, 0, sizeof(etudiant));
								continue;
							}
							if(etudiant.promo != 0)
								fwrite(&etudiant, sizeof(t_etudiant), 1, fic);
							if(etudiant.promo == promo){
								p.gEtudiant[j++] = etudiant;
							}
							memset(&etudiant, 0, sizeof(etudiant));
						}
						if(j != 0){
							p.taillePromo = j;
							p.promo = promo;
						}
						memset(&maPromo, 0, sizeof(maPromo));
						maPromo = p;
						fclose(fic);
						fclose(ficLE);
						remove(FICHIER_ETUDIANTS);
						rename("prov", FICHIER_ETUDIANTS);
						if((ficLE = fopen(FICHIER_ETUDIANTS,"ab+")) == NULL)
						{
							problemeFichier(FICHIER_ETUDIANTS);
							exit(EXIT_FAILURE);
						}
						printf("\t\tSUPPRESION TERMINE !!!");
					}
				}
				
				affichage_menu(promo);
				break;
				
			case 12://Quitter l'édition de la promotion
				if(promo == 0){
					msgMauvaisChoix();
					affichage_menu(promo);
					break;
				}
				
				memset(&maPromo, 0, sizeof(maPromo));
				memset(&etudiant, 0, sizeof(etudiant));
				printf("\n\n\t<== Vous avez quitter l'%cdition de la promotion de < %d > ==>\n\n", -126, promo);
				promo = 0;
				
				affichage_menu(promo);
				break;
				
			default:
				if(opt == 20){
					printf("\nVous allez quitter le programme. Continuer ? ( O ) ");
					rep = getchar();
					fflush(stdin);
					if(rep != 'O' && rep != 'o'){
						opt = 0;
						affichage_menu(promo);
						break;
					}
					else{
						printf("\n\n\t\tA la prochaine !\n\n");
						break;
					}
				}
				
				msgMauvaisChoix();
				affichage_menu(promo);
				break;
		}
	}while(opt != 20);
	
	fclose(ficLE);
	
	exit(EXIT_SUCCESS);
}

void affichage_menu(int promo){
	printf("\n\n\t\t\t    <==*** MENU ***==>\n");
	if(promo == 0){
		printf("\n\t=> Option ( 1 ) : Afficher les promotions disponibles");
		printf("\n\t=> Option ( 2 ) : Chercher des homonymes dans les noms des %ctudiants de toutes les promotions", -126);
		printf("\n\t=> Option ( 3 ) : Chercher avec un pr%cfixe dans les noms des %ctudiants de toutes les promotions", -126, -126);
		printf("\n\t=> Option ( 4 ) : Ajouter une promotion");
		printf("\n\t=> Option ( 5 ) : Editer ou afficher une promotion");
	}
	else{
		printf("\t\t/*** Promotion en %cdition < %d > ***/", -126, promo);
		printf("\n\t=> Option (  6 ) : Afficher la promotion", promo);
		printf("\n\t=> Option (  7 ) : Afficher un %ctudiant de la promotion", -126);
		printf("\n\t=> Option (  8 ) : Chercher des homonymes dans les noms des %ctudiants de la promotion", -126);
		printf("\n\t=> Option (  9 ) : Chercher avec un pr%cfixe dans les noms des %ctudiants de la promotion", -126, -126);
		printf("\n\t=> Option ( 10 ) : Ajouter un %ctudiant %c la promotion", -126, -123);
		printf("\n\t=> Option ( 11 ) : Supprimer un %ctudiant de la promotion", -126);
		printf("\n\t=> Option ( 12 ) : Quitter l'%cdition de la promotion < %d >", -126, promo);
	}
		
	printf("\n\t\t==\t==\t==");
	printf("\n\t=> Option ( 20 ) : QUITTER le programme !");
		
	printf("\n\t\tChoisissez une option : ");
}

void msgMauvaisChoix(){
	printf("\n\n\t!!! CHOISISSEZ PARMIS LES OPTIONS PROPOSEE !!!\n");
}

void problemeFichier(char *nomFichier){
	printf("Impossible de cr%cer / d'avoir acc%cs au fichier \" %s \" !\n", -126, -118, nomFichier);
}
