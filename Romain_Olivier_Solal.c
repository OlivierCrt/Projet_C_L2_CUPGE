#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h> //cryptage
#include "Romain_Olivier_Solal.h" 
#include <jansson.h>

typedef struct s_date {
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
}Date;

typedef struct s_trajet {
    Ville* villes[];
    Date* dates;
    Conducteur conducteur;
    Client** clients;
}Trajet;

typedef struct s_ville {
    char* nom;
}Ville;

typedef struct s_conducteur {
    char* id;
    int mdp;
}Conducteur;

typedef struct s_client {
    char* id;
    int mdp
}Client;

typedef struct s_admin {
    char* id;
    int mdp;
}Admin;

Admin admin;
Conducteur* conducteurs;
Client* clients;
Trajet* trajets;
Ville* villes*

int NB_conducteurs = 0;
int NB_clients = 0;
int NB_trajets = 0;
int NB_villes = 0;


//----------------DEBUT DU CODE-----------------

void login(Conducteur* conducteurs, Client* clients, Admin admin) {
    int choix;
    printf("Voulez-vous vous connecter en tant que : \n");
    printf("1- Administrateur\n");
    printf("2- Conducteur\n");
    printf("3- CLient\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        login_admin(admin);
    }
    if (choix == 2) {
        login_conducteur(conducteurs);
    }
    if (choix == 3{
        login_client(clients);
    }
    if (choix == 4){
        printf("Au revoir !\n");
        exit(0);
    }
    else{ 
        printf("Choix invalide\n");
        login(conducteurs, clients, admin);
    }
}

//-------------------LOGIN---------------------------

void login_admin(admin) {
    int id;
    int mdp;
    printf("Identifiant : ");
    scanf("%d", &id);
    printf("Mot de passe : ");
    scanf("%d", &mdp);
    if ((admin->id == id) && (->mdp == mdp)) {
        printf("Bienvenue %s !\n", admin->id);
        menu_admin(conducteurs, clients, trajets, villes);
    }
    printf("Identifiant ou mot de passe incorrect\n");
    login_admin(admin);
}

void login_conducteur(Conducteur* conducteurs){
    int id;
    int mdp;
    printf("Identifiant : ");
    scanf("%d", &id);
    printf("Mot de passe : ");
    scanf("%d", &mdp);
    for (int i = 0; i < NB_conducteurs; i++) {
        if ((conducteurs[i]->id == id) && (conducteurs[i]->mdp == mdp)) {
            printf("Bienvenue %s !\n", conducteurs[i]->id);
            menu_conducteur(conducteurs[i], clients, trajets, villes);
        }
    }
    printf("Identifiant ou mot de passe incorrect\n");
    login_conducteur(conducteurs);
}

    void login_client(clients) {
        int id;
        int mdp;
        printf("Identifiant : ");
        scanf("%d", &id);
        printf("Mot de passe : ");
        scanf("%d", &mdp);
        for (int i = 0; i < NB_clients; i++) {
            if ((clients[i]->id == id) && (clients[i]->mdp == mdp)) {
                printf("Bienvenue %s !\n", clients[i]->id);
                menu_client(conducteurs, clients[i], trajets, villes);
            }
        }
        printf("Identifiant ou mot de passe incorrect\n");
        login_client(clients);
    }


//-------------------ADMIN---------------------------

void menu_admin(Conducteur* conducteurs, Client* clients, Trajet* trajets, Ville* villes) {
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
    if (choix == 1) {
        add_v(villes);
    }
    if (choix == 2) {
        edit_v(villes, ville);
    }
    if (choix == 3{
        sup_v(villes, ville);
    }
    if (choix == 4) {
        export_json(Concducteurs, Clients, trajets, villes, const char* chemin_pc);
    }
    if (choix == 5) {
        import_json(Concducteurs, Clients, trajets, villes, const char* chemin_pc);
    }
    if (choix == 6) {
        admin_mdp_conducteur(conducteurs);
    }
    if (choix == 7){
        admin_mdp_client(clients);
    }
    if (choix == 8) {
        printf("Au revoir !\n");
        exit(0);
    }
    else {
        printf("Choix invalide\n");
        menu_admin(conducteurs, clients, trajets, villes);
    }
}

//1
void add_v(Ville* villes) {
    printf("Nom de la ville à ajouter : ");
    char nom[50];
    scanf("%s", nom);
    Ville ville = { nom };
    villes[NB_villes] = ville;
    printf("La ville %s a bien été ajoutée !\n", nom);
    NB_VILLES++;
    return;
}

//2
void edit_v(Ville* villes, Ville ville) {
    printf("Nom de la ville à modifier : ");
    char nom[50];
    scanf("%s", nom);
    for (int i = 0; i < NB_villes; i++) {
        if (strcmp(villes[i]->nom, nom) == 0) {
            printf("Nouveau nom de la ville : ");
            scanf("%s", villes[i]->nom);
            printf("La ville %s a été modifiée avec succès !\n", villes[i]->nom);
            return;
        }
    }
    printf("La ville %s n'a pas été trouvée\n", nom);
    edit_v(villes, ville);
}

//3
void sup_v(Ville* villes, Ville ville) {
    printf("Nom de la ville à supprimer : ");
    char nom[50];
    scanf("%s", nom);
    for (int i = 0; i < NB_villes; i++) {
        if (strcmp(villes[i]->nom, nom) == 0) {
            for (int j = i; j < NB_villes - 1; j++) {
                villes[j] = villes[j + 1];
            }
            NB_Villes--;
            printf("La ville %s a été supprimée avec succès !\n", nom);
            return;
        }
    }
    printf("La ville %s n'a pas été trouvée\n", nom);
    sup_v(villes, ville);
}

//4
void export_json(Conducteur* Concducteurs, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc) {
    //pas la ref
    return;
}

//5
void import_json(Conducteur* Concducteur, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc) {
    //pas la ref
    return;
}

//6
void admin_mdp_conducteur(Conducteur* conducteurs) {
    printf("ID du conducteur dont vous souhaitez modifier le mot de passe : ");
    char id[50];
    scanf("%s", id);
    for (int i = 0; i < NB_conducteurs; i++) {
        if (strcmp(conducteurs[i]->id, id) == 0) {
            printf("Nouveau Mot de passe : ");
            scanf("%s", conducteurs[i]->mdp);
            printf("Le mot de passe %s a été modifiée avec succès !\n", conducteurs[i]->id);
            return;
        }
    }
    printf("Le conducteur %s n'a pas été trouvée\n", conducteurs[i]->id);
    admin_mdp_conducteur(conducteurs);
}

//7
void admin_mdp_client(Client* clients){
    printf("ID du client dont vous souhaitez modifier le mot de passe : ");
    char id[50];
    scanf("%s", id);
    for (int i = 0; i < NB_clients; i++) {
        if (strcmp(clients[i]->id, id) == 0) {
            printf("Nouveau Mot de passe : ");
            scanf("%s", clients[i]->mdp);
            printf("Le mot de passe %s a été modifiée avec succès !\n", clients[i]->id);
            return;
        }
    }
    printf("Le client %s n'a pas été trouvée\n", clients[i]->id);
    admin_mdp_client(clients);
}

//--------------CONDUCTEUR---------------

void menu_conducteur(Conducteur conducteur, Client* clients, Trajet* trajets, Ville* villes) {
    int choix;
    printf("Vous voulez : \n");
    printf("1- Créer une offre\n");
    printf("2- Afficher vos trajets\n");
    printf("3- Changer vos logs\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        creer_trajet(conducteur, trajets, villes);
    }
    if (choix == 2) {
        afficher_trajets(trajets, conducteur);
    }
    if (choix == 3{
        changer_logs_conducteur(conducteur);
    }
    if (choix == 4){
        printf("Au revoir !\n");
        exit(0);
    }
    else {
        printf("Choix invalide\n");
        menu_conducteur(conducteur, clients, trajets, villes);
    }
}

//1
void creer_trajet(Conducteur conducteur, Trajet* trajets, Ville* villes);

//2
void afficher_trajets(Trajet* trajets, Conducteur conducteur);

//3
void changer_logs_conducteur(Conducteur conducteur);


//-----------------CLIENT----------------

void menu_client(Conducteur* conducteur, Client* clients, Trajet* trajets, Ville* villes) {
    int choix;
    printf("Vous voulez : \n");
    printf("1- Chercher un trajet\n");
    printf("2- Reserver un trajet\n");
    printf("3- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        creer_trajet(conducteur, trajets, villes);
    }
    if (choix == 2) {
        afficher_trajets(trajets, conducteur);
    }
    if (choix == 3{
        changer_logs_conducteur(conducteur);
    }
    if (choix == 4) {
        printf("Au revoir !\n");
            exit(0);
    }
    else {
        printf("Choix invalide\n");
        menu_client(conducteurs, client, trajets, villes);
    }
}
    
//1
void chercher_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs); // osef des conducteur 

//2
void reserver_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs, Client client); //idem 

