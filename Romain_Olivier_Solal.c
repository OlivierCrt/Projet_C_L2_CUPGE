#ifndef BLABLACAR_H
#define BLABLACAR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h> //cryptage
#include "Romain_Olivier_Solal.h"

typedef struct s_date {
  int annee;
  int mois;
  int jour;
  int heure;
  int minute;
}Date;

typedef struct s_trajet{
  Ville* villes[];
  Date* dates;
  Conducteur conducteur;
  Client** clients;
}Trajet;

typedef struct s_ville{
  char* nom
}Ville;

typedef struct s_conducteur{
  char* nom ;
  char* prenom;
  int mdp;
}Conducteur;

typedef struct s_client{
  char* nom ;
  char*prenom;
}Client;

typedef struct s_admin{
  char* nom;
  char* prenom;
  int mdp;
}Admin;



//0-
void login(Conducteur* conducteurs, Client* clients, Admin admin ); 
// 1- Gestion villes
void add_v(Ville* villes);
void edit_v(Ville* villes,Ville ville);
void sup_v(Ville* villes, Ville ville);
//2- Exportation 
void export_json(Conducteur* Concducteurs, Client* Clients, Trajet* trajets, Ville* villes , const char* chemin_pc); // une fonction par chaque liste à export/ import ? 
void import_json(Conducteur* Concducteur, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc); // faut-il fournir la taille pour l'import/l'export ?
//3- Admin  
void admin_mdp_conducteur(Conducteur* conducteurs, Conducteur conducteur);
void admin_mdp_client(Client* clients, Client client);
// 4 Créer Offre
void creer_trajet(Conducteur conducteur, Trajet* trajets, Ville* villes); // Conducteur* ou Conducteur || note : dans la struct "trajet" on a "horaire" qui est une liste dont  x eme element appartient à l'horaire de départ de la x eme ville du trajet). Dans la meme idée on a aussi une liste avec le nombre de passagers (0,1, ou 2) pour chaque troncon (ou plutot le nom de chaque client a la place de 0 1 2 et on r
//5 Afficher tous les trajets du conducteur connecté
void afficher_trajets(Trajet* trajets, Conducteur conducteur); 
//6 changer ses logs
void changer_logs_conducteur( Conducteur conducteur);  // besoin de conducteur* ?
//7-
void chercher_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs); // pour la date, rechercher un jour, une heure ou une plage horaire ?
//8-
void reserver_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs, Client client); // on comprend ici que reservation et modification sont des synonymes. est ce juste ? ou y a t il 2 fonctions/actions distinctes ?
//9-
void exit();

#endif
