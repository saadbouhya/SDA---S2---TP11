#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NBSKI 12
#define MAXV 50

#include "ski.h"
int menu();
void Afficherville(char *Ville);
void trier(T_Skieur *S);
int recherche(char *ville);
void Produire_villes();
void Afficherlesvilles();
void AfficherlesvillesFichier(FILE *fic);
void AffichervilleFichier(char *Ville, FILE *fic);
void produireGenerale();
char derniereligne (char nom[30], char derniere[50]);
void afficherVilleGenerale(char *ville, T_Skieur *S);
void trierScore(T_Skieur *S);

int main()
{
FILE *fic=NULL;
T_Skieur S;
int choix;
char nom_vil[MAXV];


do
{
	choix=menu();
	switch(choix){
		case 1:

		printf("saisir le nom de la ville\n");
		scanf("%s", nom_vil);
    if (recherche(nom_vil) == 1) {
      Afficherville(nom_vil);
    }
		else {
      printf("Cette ville n'existe pas.\n");
    }

		break;

		case 2:
		Afficherlesvilles();
		break;

		case 3:
    Produire_villes();
		break;

    case 4:
      produireGenerale();
			break;

		case 0:
		exit(1);
	}
	
	} while (choix != 0);



return 0;
}

















int menu() {
	int ch;
	printf("Faites votre choix\n");

	printf("1- Afficher les skieurs d'une ville (de votre choix)\n");
	printf("2- Afficher les skieurs de toutes les villes\n");
	printf("3- Produir un fichier txt des skieurs de toutes les villes\n");
	printf("4- Produir le fichier general.txt\n");
	printf("0- Exit\n");
	scanf("%d", &ch);

	return ch;
}

void Afficherville(char *Ville){
	FILE *fic=NULL;
	T_Skieur s[NBSKI];
	int i=0;

	strcat(Ville, ".dat");

	fic=fopen(Ville,"r");
  
	if (fic != NULL)
	{
		printf("*********  %s  ********* \n", Ville);
		do
		{
			fread(&s[i],1,sizeof(T_Skieur),fic);
			i++;
		} while (!feof(fic));

		trier(s);


			s[0].nbpoints=20; s[1].nbpoints=16; s[2].nbpoints=12; s[3].nbpoints=8; s[4].nbpoints=4; 
			i=0;
			while(i<NBSKI)
			{			
				printf("%10s  %5d  %5d  %3d \n",s[i].nom,s[i].temps.minutes*60+s[i].temps.secondes,s[i].dossart,s[i].nbpoints);
				i++;
				 
				if(i > 4)
					s[i].nbpoints=0;
			}
					i=0;	
		
		}
		
	fclose(fic);

	}


void trier(T_Skieur *S){
int i, j;
int indice;
T_Skieur temp;
	for(i=1;i< NBSKI;i++)
	{
		indice=i-1;
		for(j=i;j<NBSKI;j++)
		{
			if((S[indice].temps.minutes*60+S[indice].temps.secondes)>(S[j].temps.minutes*60 + S[j].temps.secondes) ||	((S[indice].temps.minutes*60+S[indice].temps.secondes)==(S[j].temps.minutes*60 + S[j].temps.secondes) && (S[indice].dossart<S[j].dossart)))
							indice=j;
						}
						temp=S[i-1];
						S[i-1]=S[indice];
						S[indice]=temp;	
					}	
}




void Afficherlesvilles(){
	FILE *fic= NULL;
	char nomV[MAXV];
	fic= fopen("courses.txt","r");
	if (fic!=NULL)
	{
		do
		{
			fgets(nomV,MAXV,fic); 
        nomV[strlen(nomV)-1]='\0';
       if (!feof(fic))
 				Afficherville(nomV);
		} while (!feof(fic));
      derniereligne ("courses.txt" , nomV);
      Afficherville(nomV);
	}
	 else printf("Le fichier courses.txt n'existe pas !!\n");
}

int recherche(char *ville) {
  FILE *fic = NULL;
  int res = 0;
  char mot[MAXV];
  fic = fopen("courses.txt","r");
  while (!feof(fic))
  {
    fgets(mot,MAXV,fic);
    mot[strlen(mot)-1]='\0';
    if(strcmp(mot,ville) == 0) {
      res = 1;
      return res;
    }
  }
  if(res == 0)
    return 0;
  
}

void Produire_villes() {
  FILE *fic2 = NULL;

  fic2=fopen("villes.txt","wr");
  AfficherlesvillesFichier(fic2);
  fclose(fic2);

}

void AffichervilleFichier(char *Ville, FILE *fic2) {
  FILE *fic=NULL;
	T_Skieur s[NBSKI];
	int i=0;

	strcat(Ville, ".dat");

	fic=fopen(Ville,"r");
  
	if (fic != NULL)
	{
		fprintf(fic2,"********* %s********* \n", Ville);

		do
		{
			fread(&s[i],1,sizeof(T_Skieur),fic);
			i++;
		} while (!feof(fic));

		trier(s);

			s[0].nbpoints=20; s[1].nbpoints=16; s[2].nbpoints=12; s[3].nbpoints=8; s[4].nbpoints=4; 
			i=0;
			while(i<NBSKI)
			{			
				fprintf(fic2,"%10s  %5d  %5d  %3d \n",s[i].nom,s[i].temps.minutes*60+s[i].temps.secondes,s[i].dossart,s[i].nbpoints);
				i++;
				
				if(i > 4)
					s[i].nbpoints=0;
			}
					i=0;	
		
		}
		
	fclose(fic);
  

}


void AfficherlesvillesFichier(FILE *fic2) {
  FILE *fic= NULL;
	char nomV[MAXV];
	fic= fopen("courses.txt","r");
	if (fic!=NULL)
	{
		do
		{
			fgets(nomV,MAXV,fic);
 			nomV[strlen(nomV)-1]='\0';
 			if (!feof(fic))
 				AffichervilleFichier(nomV, fic2);
		} while (!feof(fic));
      derniereligne ("courses.txt" , nomV);
      AffichervilleFichier(nomV, fic2);
	}
}

void produireGenerale() {
  T_Skieur S[NBSKI];

  strcpy(S[0].nom, "Janka");
  strcpy(S[1].nom, "Svindal");
  strcpy(S[2].nom, "Miller");
  strcpy(S[3].nom, "Pinturault");
  strcpy(S[4].nom, "Kostelic");
  strcpy(S[5].nom, "Hirscher");
  strcpy(S[6].nom, "Yule");
  strcpy(S[7].nom, "Tomba");
  strcpy(S[8].nom, "Maier");
  strcpy(S[9].nom, "Grange");
  strcpy(S[10].nom, "Vidal");
  strcpy(S[11].nom, "Cuche");

	for (int i = 0; i < 12; i++) {
		S[i].nbpoints = 0;
  }

  FILE *fic= NULL;
	char nomV[MAXV];
	fic= fopen("courses.txt","r");
	if (fic!=NULL)
	{
    int i=0;

			while (i<12) {
				do {
					fgets(nomV,MAXV,fic);
					nomV[strlen(nomV)-1]='\0';
					if (!feof(fic))
						afficherVilleGenerale(nomV, &S[i]);
				} while (!feof(fic));
					derniereligne ("courses.txt" , nomV);
					afficherVilleGenerale(nomV, &S[i]);
					i++;
					rewind(fic);
			}
			
	}

	trierScore(S);
  printf("\n------- Classement Generale --------\n");
  for (int i = 0; i < 12; i++) {
    printf("%10s   %3d\n", S[i].nom, S[i].nbpoints);
  }
  fclose(fic);

	FILE *fic2 = NULL;
  fic2=fopen("generale.txt","wr");
	fprintf(fic2,"*********   Classement Generale  ********* \n");
	for (int i=0; i < 12; i++) {
			fprintf(fic2,"%10s   %3d \n", S[i].nom, S[i].nbpoints);
	}
	fclose(fic2);
}



// Source de la fonction derniereligne  https://codes-sources.commentcamarche.net/forum/affich-1574416-lecture-de-la-derniere-ligne-d-un-fichier-txt
char derniereligne (char nom[30], char derniere[50]) 
{

FILE *fichier;
fichier = fopen(nom, "r");
if (fichier != NULL)
{
while(fgets(derniere, 50, fichier) != NULL){
}
fclose(fichier);
}
}

void afficherVilleGenerale(char *ville, T_Skieur *S) {
  FILE *fic=NULL;
	T_Skieur s[NBSKI];
	int i=0;

	strcat(ville, ".dat");

	fic=fopen(ville,"r");
  
	if (fic != NULL)
	{
		do
		{
			fread(&s[i],1,sizeof(T_Skieur),fic);
			i++;
		} while (!feof(fic));


		trier(s);


			s[0].nbpoints=20; s[1].nbpoints=16; s[2].nbpoints=12; s[3].nbpoints=8; s[4].nbpoints=4; 
			i=0;
			while(i<NBSKI)
			{		
				if(i > 4) {
					s[i].nbpoints=0;
				}

				if (strcmp(S->nom, s[i].nom) == 0) { 
					S->nbpoints += s[i].nbpoints;
				}
    		
				i++;
				
			}
	}
		

  
		
		
	fclose(fic);
}

void trierScore(T_Skieur *S) {
	int i,j,indice;
	T_Skieur aux;
		for(i=1;i<12;i++)
		{
			indice=i-1;
			for(j=i;j<12;j++)
			{
				if((S[indice].nbpoints<S[j].nbpoints) || ((S[indice].nbpoints==S[j].nbpoints) && (S[indice].dossart<S[j].dossart)))
								indice=j;
							}
							aux=S[i-1];
							S[i-1]=S[indice];
							S[indice]=aux;	
						}	
}