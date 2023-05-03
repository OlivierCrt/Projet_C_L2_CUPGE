#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h> //cryptage
#include "Romain_Olivier_Solal.h"

//mettre des constantes qui indiquent la taille des listes : nb client ; nb conducteur ; nb ville

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
  char* nom;
}Ville;

typedef struct s_conducteur{
  char* id;
  int mdp;
}Conducteur;

typedef struct s_client{
  char* id;
}Client;

typedef struct s_admin{
  char* id;
  int mdp;
}Admin;


//---------------Start-----------------------
//0-
void login(Conducteur* conducteurs, Client* clients, Admin admin ); 
//---------------Menu Admin-------------------
//1- Gestion villes
void add_v(Ville* villes);
void edit_v(Ville* villes,Ville ville);
void sup_v(Ville* villes, Ville ville);
//2- Exportation 
void export_json(Conducteur* Concducteurs, Client* Clients, Trajet* trajets, Ville* villes , const char* chemin_pc); 
void import_json(Conducteur* Concducteur, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc); 
//3- Admin  
void admin_mdp_conducteur(Conducteur* conducteurs, Conducteur conducteur);
void admin_mdp_client(Client* clients, Client client);
//---------------Menu Conducteur-------------------
// 4 Créer Offre
void creer_trajet(Conducteur conducteur, Trajet* trajets, Ville* villes);  
//5 Afficher tous les trajets du conducteur connecté
void afficher_trajets(Trajet* trajets, Conducteur conducteur); 
//6 changer ses logs
void changer_logs_conducteur( Conducteur conducteur); 
//---------------Menu Client-------------------
//7-
void chercher_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs); 
//8-
void reserver_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs, Client client); 
//---------------Commun aux 4 menus-------------------
//9-
void exit();

//----------------DEBUT DU CODE-----------------

void login(Conducteur* conducteurs, Client* clients, Admin admin) {
    int id;
    int mdp;
    int choix;
    printf("Voulez-vous vous connecter en tant que : \n");
    printf("1- Conducteur\n");
    printf("2- Client\n");
    printf("3- Administrateur\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    switch (choix) {
    case 1: // conducteur
        printf("Identifiant : ");
        scanf("%d", &id);
        printf("Mot de passe : ");
        scanf("%d", &mdp);
        for (int i = 0; i < NB_CONDUCTEURS; i++) {
            if ((conducteurs[i].id == id) && (conducteurs[i].mdp == mdp)) {
                printf("Bienvenue %s !\n", conducteurs[i].id);
                menu_conducteur(conducteurs[i], clients, trajets, villes);
                return;
            }
        }
        printf("Identifiant ou mot de passe incorrect\n");
        break;
    case 2: // client
        printf("Identifiant : ");
        scanf("%d", &id);
        printf("Mot de passe : ");
        scanf("%d", &mdp);
        for (int i = 0; i < NB_CLIENTS; i++) {
            if ((clients[i].id == id) && (clients[i].mdp == mdp)) {
                printf("Bienvenue %s !\n", clients[i].id);
                menu_client(clients[i], trajets, villes, conducteurs);
                return;
            }
        }
        printf("Identifiant ou mot de passe incorrect\n");
        break;
    case 3: // admin
        printf("Identifiant : ");
        scanf("%d", &id);
        printf("Mot de passe : ");
        scanf("%d", &mdp);
        if ((admin.id == id) && (admin.mdp == mdp))) {
            printf("Bienvenue %s !\n", admin.id);
            menu_admin(conducteurs, clients, trajets, villes);
            return;
        }
        printf("Identifiant ou mot de passe incorrect\n");
        break;
    case 4:
        printf("Au revoir !\n");
        exit(0);
    default:
        printf("Choix invalide\n");
    }
    login(conducteurs, clients, admin);
}


//-------------------ADMIN---------------------------

void menu_admin(Conducteur* conducteurs, Client* clients, Trajet* trajets,Ville* villes){
    int choix;
    printf("Vous voulez : \n");
    printf("1- Ajouter une ville\n");
    printf("2- Modifier une ville\n");
    printf("3- Supprimer une ville\n");
    printf("4- Exporter un JSON\n");
    printf("5- Importer un JSON\n");
    printf("6- Modifier le profil d'un conducteur\n");
    printf("7- Modifier le profil d'un client\n");
    printf("8- Quitter le programme\n");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
        //void add_v(Ville* villes) {
          printf("Nom de la ville à ajouter : ");
          char nom[50];
          scanf("%s", nom);
          Ville ville = { nom };
          villes[NB_VILLES] = ville;
          printf("La ville %s a bien été ajoutée !\n", nom);
          NB_VILLES++;
          return; 
        }
        printf("Erreur\n");
        break;
   case 2:
        //void edit_v(Ville* villes, Ville ville) {
          printf("Nom de la ville à modifier : ");
          char nom[50];
          scanf("%s", nom);
          for (int i = 0; i < NB_VILLES; i++) {
              if (strcmp(villes[i].nom, nom) == 0) {
                  printf("Nouveau nom de la ville : ");
                  scanf("%s", villes[i].nom);
                  printf("La ville %s a été modifiée avec succès !\n", villes[i].nom);
                  return;
        printf("Erreur\n");
        break;
   case 3:
        //void sup_v(Ville* villes, Ville ville) {
           printf("Nom de la ville à supprimer : ");
           char nom[50];
           scanf("%s", nom);
           for (int i = 0; i < NB_VILLES; i++) {
             if (strcmp(villes[i].nom, nom) == 0) {
               for (int j = i; j < NB_VILLES - 1; j++) {
                 villes[j] = villes[j + 1];
               }
             NB_VILLES--;
             printf("La ville %s a été supprimée avec succès !\n", nom);
             return;
             }
           }
           printf("La ville %s n'a pas été trouvée\n", nom);   
           break;
   case 4:
        return;
        
        printf("Erreur\n");
        break;
   case 5:
        return;
        
        printf("Erreur\n");
        break;
   case 6:
        return;
        
        printf("Erreur\n");
        break;
   case 7:
        return;
        
        printf("Erreur\n");
        break;
   case 8:
        return;
        
        printf("Erreur\n");
        break; 
    default:
        printf("Choix invalide\n");
    }
    void menu_admin(Conducteur* conducteurs, Client* clients, Trajet* trajets,Ville* villes);
}


//--------------CONDUCTEUR---------------
  
void menu_conducteur(Conducteur conducteur, Client* clients, Trajet* trajets,Ville* villes){
  int choix;
    printf("Vous voulez : \n");
    printf("1- Créer une offre\n");
    printf("2- Afficher vos trajets\n");
    printf("3- Changer vos logs\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
        return;
        
        printf("Erreur\n");
        break;
   case 2:
        return;
        
        printf("Erreur\n");
        break;
   case 3:
        return;
        
        printf("Erreur\n");
        break;
   case 4:
        return;
        
        printf("Erreur\n");
        break;
    default:
        printf("Choix invalide\n");
    }
    void menu_conducteur(Conducteur conducteur, Client* clients, Trajet* trajets,Ville* villes);
}

//-----------------CLIENT----------------

void menu_client(Conducteur* conducteur, Client* clients, Trajet* trajets,Ville* villes){
  int choix;
    printf("Vous voulez : \n");
    printf("1- Chercher un trajet\n");
    printf("2- Reserver un trajet\n");
    printf("3- Quitter le programme\n");
    scanf("%d", &choix);
    switch (choix) {
    case 1:
        return;
        
        printf("Erreur\n");
        break;
   case 2:
        return;
        
        printf("Erreur\n");
        break;
   case 3:
        return;
        
        printf("Erreur\n");
        break;
    default:
        printf("Choix invalide\n");
    }
    void menu_client(Conducteur* conducteur, Client* clients, Trajet* trajets,Ville* villes);
}


