#include "promotion.h"

t_date saisis_dNaissance(void){
	t_date bDate;
	printf("Date de naissance :");
	printf("\nEntrez le jour : ");
	scanf("%d", &bDate.jour);
	fflush(stdin);
	
	printf("Entrez le mois : ");
	scanf("%d", &bDate.mois);
	fflush(stdin);
	
	printf("Entrez l'ann%ce : ", -126);
	scanf("%d", &bDate.an);
	fflush(stdin);
	
	return bDate;
}

// 	d)
void saisis_etudiant(t_etudiant *etudiant, int p, FILE *fic){
	printf("\nEntrez le pr%cnom : ", -126);
	scanf("%s", &etudiant->prenom);
	fflush(stdin);
	
	printf("Entrez le nom : ");
	scanf("%s", &etudiant->nom);
	fflush(stdin);
	
	etudiant->dNaissance = saisis_dNaissance();
	
	printf("Entrez le genre (0 pour masculin et 1 pour f%cminin): ", -126);
	scanf("%d", &etudiant->genre);
	fflush(stdin);
	
	etudiant->promo = p;
	
	t_etudiant estud = (*etudiant);
	fwrite(&estud, sizeof(t_etudiant), 1, fic);
}

//	e)
void affiche_etudiant(t_etudiant etudiant){
	struct tm date;
	char format[10];
	
	printf("\n    Affichage de l'%ctudiant :\n", -126);
	printf("Nom : \t\t\t%s\nPr%cnom : \t\t%s\nDate de naissance :\tle %d ", etudiant.nom, -126, etudiant.prenom, etudiant.dNaissance.jour);
	
	date.tm_mon = etudiant.dNaissance.mois -1;
	strftime(format, 10, "%B", &date);
	printf("%s", format);
		
	printf(" %d", etudiant.dNaissance.an);
	
	if(etudiant.genre == Masculin)
		printf("\nGenre : \t\tMasculin");
	else
		printf("\nGenre : \t\tF%cminin", -126);
		
	printf("\nPromotion : \t\t%d", etudiant.promo);
}

//	g)
void saisis_promotion(t_promo *promo, int p, FILE *fic){
	int i = 0;
	char rep;
	printf("\t\tNouvelle promotion :\n");
	do{
		t_etudiant estud;
		printf("-- Etudiant n.%d --", i);
		saisis_etudiant(&estud, p, fic);
		promo->gEtudiant[i] = estud;
		
		if(++i < TAILLE_MAX_PROMO)
			do{
				printf("Voulez-vous saisir un autre %ctudiant (O/N) ? ", -126);
				scanf("%c", &rep);
				fflush(stdin);
			}while(rep != 'O' && rep != 'o' && rep != 'N' && rep != 'n');
		else{
			printf("\n\t\t!!! TAILLE MAXIMALE DE LA PROMOTION ATTEINTE !!!");
			break;
		}
	}while(rep == 'O' || rep == 'o');
	promo->taillePromo = i;
	promo->promo = p;
	
	printf("\n %d %ctudiant(s) ont %ct%c saisis.\n", i, -126, -126, -126);
}

//	h)
void affiche_promotion(t_promo promo){
	int i, j;
	struct tm date;
	char format[10];
	
	printf(" %c", -55);
	for(j=0 ; j<=78 ; j++)
		printf("%c", -51);
	printf("%c", -69);
	printf("\n %cNum%cro   Pr%cnom                Nom                   Date de naissance :       %c", -70, -126, -126, -70);//printf("%s ","Num", -126, "ro", "Pr", -126, "nom", "Nom","Date de naissonace");//printf("Num%cro\tPr%cnom\t\tNom\t\tDate de naissance :", -126, -126);
	printf("\n %c", -52);
	for(j=0 ; j<=78 ; j++)
		printf("%c", -51);
	printf("%c", -71);
	
	for(i = 0 ; i < promo.taillePromo ; i++){
		printf("\n %c%6d.", -70, i);
		printf("  %-20s  %-20s", promo.gEtudiant[i].prenom, promo.gEtudiant[i].nom);
		if(promo.gEtudiant[i].genre == Masculin)
			printf("  n%c  le %02d", -126, promo.gEtudiant[i].dNaissance.jour);
		else
			printf("  n%ce le %02d", -126, promo.gEtudiant[i].dNaissance.jour);
		
		date.tm_mon = promo.gEtudiant[i].dNaissance.mois -1;
		strftime(format, 10, "%B", &date);//
		printf(" %10s", format);
		
		printf(" %4d %c", promo.gEtudiant[i].dNaissance.an, -70);
	}
	
	printf("\n %c", -56);
	for(j=0 ; j<=78 ; j++)
		printf("%c", -51);
	printf("%c", -68);
}

//	i)
t_promo initialise_promotion(){
	t_promo donnees = {
		9,
		2005,
		{
			{ "Emreoglu", "Emre",			{ 20, 11, 1985}, 0, 2005},
			{ "Ozturk", "Zeynep", 			{  8,  8, 1988}, 1, 2005},
			{ "Ozanoglu", "Ozan", 			{ 10, 10, 1986}, 0, 2005},
			{ "Canoglu", "Can", 			{  8,  8, 1984}, 0, 2005},
			{ "Kucuk", "Naz", 				{  2,  2, 1985}, 1, 2005},
			{ "Kucukkarakurt", "Dilek", 	{  7,  7, 1985}, 1, 2005},
			{ "Onay", "Sevgi", 				{  4,  4, 1985}, 1, 2005},
			{ "Kocak", "Ozgur", 			{  6,  5, 1985}, 0, 2005},
			{ "Kucuk", "Hakan", 			{  3,  3, 1986}, 0, 2005}
		}
	};
	
	return donnees;
}

//	j)
void cherche_homonymes(t_promo p, char* nom){
	int i;
	verification zeroResult = Oui;
	printf("R%csultat de la recherche pour la cha%cne \"%s\" :", -126, -116, nom);
	
	for(i = 0 ; i < p.taillePromo ; i++){
		if(strcmp(nom, p.gEtudiant[i].nom) == 0){
			affiche_result_recherche(&p, &i);
			zeroResult = Non;
		}
	}
	if(zeroResult == Oui)
		printf("\n Aucune correspondance pour \"%s\" ", nom);
}

//	k)
void cherche_prefixe(t_promo p, t_promo* res, char* prefixe){
	int i, j = 0, taillePref = strlen(prefixe);
	char nomCoup[TAILLE_MAX_NOM] = "";
	for(i = 0 ; i < p.taillePromo ; i++){
		strncpy(nomCoup, p.gEtudiant[i].nom, taillePref);
		if(strcmp(prefixe, nomCoup) == 0){
			res->gEtudiant[j] = p.gEtudiant[i];
			j++;
		}
	}
	res->taillePromo = j;
	if(j == 0)
		printf(" Aucune correspondance pour \"%s\" ", prefixe);
}

void affiche_result_recherche(t_promo *p1, int* i){
	struct tm date;
	char format[10];
	
	printf("\n- ");
	printf("%-22s%-22s", p1->gEtudiant[*i].prenom, p1->gEtudiant[*i].nom);
	
	if(p1->gEtudiant[*i].genre == Feminin)
		printf("n%ce le %02d ", -126, p1->gEtudiant[*i].dNaissance.jour);
	else
		printf("n%c  le %02d ", -126, p1->gEtudiant[*i].dNaissance.jour);
	
	date.tm_mon = p1->gEtudiant[*i].dNaissance.mois -1;
	strftime(format, 10, "%B", &date);
	printf("%10s", format);
	
	printf(" %04d", p1->gEtudiant[*i].dNaissance.an);
}

void affiche_liste_promotion(){
	FILE *fic;
	int promo;
	if ((fic = fopen(FICHIER_PROMO,"r")) == NULL)
	{
		printf("\nImpossible d'ouvrir le fichier \n");
	}
	else
	{
		printf("\n Liste des promotions disponibles dans la base :");
		while(!feof(fic))
		{
			fscanf(fic, "%d\n", &promo);
			printf("\n- %d", promo);
		}
		fclose(fic);
	}
}

void getAll(char *nom, FILE *fic, int opt){
	t_etudiant etudiant;
	int i = 0;
	verification zeroResult = Oui;
	struct tm date;
	char format[10];
	
	if(opt == 2){
		rewind(fic);
		printf("R%csultat de la recherche pour la cha%cne \"%s\" :", -126, -116, nom);
		while(!feof(fic)){
			fread(&etudiant, sizeof(t_etudiant), 1, fic);
			if(strcmp(nom, etudiant.nom) == 0){
				
				printf("\n- ");
				printf("%-22s%-22s", etudiant.prenom, etudiant.nom);
				
				if(etudiant.genre == Feminin)
					printf("n%ce le %02d ", -126, etudiant.dNaissance.jour);
				else
					printf("n%c  le %02d ", -126, etudiant.dNaissance.jour);
				
				date.tm_mon = etudiant.dNaissance.mois -1;
				strftime(format, 10, "%B", &date);
				printf("%10s", format);
				
				printf("%04d", etudiant.dNaissance.an);
				printf("\tPromotion : %04d", etudiant.promo);
				
				memset(&etudiant, 0, sizeof(etudiant));//pour eviter un affichage en double du dernier...
				zeroResult = Non;
			}
		}
		if(zeroResult == Oui)
			printf("\n Aucune correspondance pour \"%s\" ", nom);
	}
	else{
		rewind(fic);
		printf("R%csultat de la recherche pour le pr%cfixe \"%s\" :", -126, -126, nom);
		int j = 0, taillePref = strlen(nom);
		char nomCoup[TAILLE_MAX_NOM] = "";
		while(!feof(fic)){
			fread(&etudiant, sizeof(t_etudiant), 1, fic);
			strncpy(nomCoup, etudiant.nom, taillePref);
			if(strcmp(nom, nomCoup) == 0){
				printf("\n- ");
				printf("%-22s%-22s, ", etudiant.prenom, etudiant.nom);
				
				if(etudiant.genre == Feminin)
					printf("n%ce le %02d ", -126, etudiant.dNaissance.jour);
				else
					printf("n%c  le %02d ", -126, etudiant.dNaissance.jour);
				
				date.tm_mon = etudiant.dNaissance.mois -1;
				strftime(format, 10, "%B", &date);
				printf("%10s", format);
				
				printf(" %04d", etudiant.dNaissance.an);
				printf("\tPromotion : %04d", etudiant.promo);
				
				memset(&etudiant, 0, sizeof(etudiant));//pour eviter un affichage en double du dernier...
				zeroResult = Non;
			}
		}
		
		if(zeroResult == Oui)
			printf("\n Aucune correspondance pour \"%s\" ", nom);
	}
}
