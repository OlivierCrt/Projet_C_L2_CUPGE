#include <stdio.h>
#include <stdlib.h>
#include "Blablacar.h"

struct s_date {
  int annee;
  int mois;
  int jour;
  int heure;
  int minute;
};

struct s_listeville{
  char* listeville[9];
};

struct s_troncon{
  char* ville_depart;
  char* ville_arrive;
};

struct s_trajet{
  Troncon liste_escales[];
  Date date_trajet;
  int nb_escales;
  Conducteur conducteur_du_trajet;
  Client liste_clients[2];
};
struct s_conducteur{
  char* nom ;
  char*prenom;
  int mot_de_passe;
  
};
struct s_client{
  char* nom ;
  char*prenom;
  int mot_de_passe;
};
  
void ajouter_ville(Ville* villes, int* nb_villes){
	if(*nb_villes >= MAX_VILLES){
		printf(“Impossible d’ajouter une nouvelle ville, le nombre de villes est  atteint.\n”);
		return;
	}
char nom_ville[20];
printf(“Entrez le nom de la nouvelle ville : \n“);
scanf(“%s”, nom_ville);
for(int i=0; i<*nb_villes; i++){
		if (strcmp(nom_ville;villes[i].nom) == 0){
			printf(“La ville existe déjà dans le tableau.\n”);
			return;
		}
}
Ville nouvelle_ville;
strcpy(nouvelle_ville.nom, nom_ville);
villes[*nb_villes] = nouvelle_ville;
(*nb_villes)++;
printf(“La ville a été ajoutée avec succès !\n”);
}

void modifier_ville(Ville* villes, int nb_villes){
	char nom_ville[20];
	printf(“Quelle est la ville que vous voulez modifier : \n“);
scanf(“%s”, nom_ville);
int i;
	for( i=0; i<nb_villes; i++){
		if (strcmp(nom_ville;villes[i].nom) == 0){
			char modif_nom_ville[20];
			printf(“Quel est le nouveau nom que vous voulez attribuer à %s : \n”, nom_ville);
scanf(“%s”,modif_nom_ville);
strcpy(villes[i].nom, modif_nom_ville);
printf(“La ville %s a été modifiée avec succés.\n”,nom_ville)”;
return;
}
}
printf(“Erreur : la ville %s n’a pas été trouvée.\n”, nom_ville);
}

 void supprimer_ville(Ville* villes, int* nb_villes){
	char nom_ville[20];
	printf(“Quelle est la ville que vous voulez supprimer :\n”);
	scanf(“%s”, nom_ville);
	int i,j;
		for( i=0; i<nb_villes; i++){
		if (strcmp(nom_ville;villes[i].nom) == 0){
for (j=i; j<*nb_villes-1; j++){
	villes[j]=villes[j+1];
}
(*nb_villes)--;
printf(“La ville %s a été supprimée.\n”, nom_ville);
return;
}
}
printf(“Erreur : la ville %s n’a pas été trouvée.\n”, nom_ville);
}





