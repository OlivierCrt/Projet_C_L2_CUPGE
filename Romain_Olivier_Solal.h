#ifndef BLABLACAR_H
#define BLABLACAR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h> //cryptage

typedef struct* s_date Date;
typedef struct* s_trajet Trajet;
typedef struct* s_ville Ville;
typedef struct* s_conducteur Conducteur;
typedef struct* s_client Client;
typedef struct* s_admin Admin;

//---------------Start-----------------------
//0-
void login(Conducteur* conducteurs, Client* clients, Admin admin);
void login_admin(Admin admin);
void login_conducteur(Conducteur* conducteurs);
void login_client(Client* clients);

void menu_admin(Conducteur* conducteurs, Client* clients, Trajet* trajets, Ville* villes) {
void menu_conducteur(Conducteur conducteur, Client* clients, Trajet* trajets, Ville* villes) {
void menu_client(Conducteur* conducteur, Client* clients, Trajet* trajets, Ville* villes) {
 

//---------------Menu Admin-------------------
//1- Gestion villes
void add_v(Ville* villes);
void edit_v(Ville* villes, Ville ville);
void sup_v(Ville* villes, Ville ville);
//2- Exportation 
void export_json(Conducteur* Concducteurs, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc);
void import_json(Conducteur* Concducteur, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc);
//3- Admin  
void admin_mdp_conducteur(Conducteur* conducteurs); // pas cond solo
void admin_mdp_client(Client* clients); // pas client solo
//---------------Menu Conducteur-------------------
// 4 Créer Offre
void creer_trajet(Conducteur conducteur, Trajet* trajets, Ville* villes);
//5 Afficher tous les trajets du conducteur connecté
void afficher_trajets(Trajet* trajets, Conducteur conducteur);
//6 changer ses logs
void changer_logs_conducteur(Conducteur conducteur);
//---------------Menu Client-------------------
//7-
void chercher_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs); // osef des conducteurs (sauf si ca rentre dans la recherche)
//8-
void reserver_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs, Client client); //idem 
//---------------Commun aux 4 menus-------------------
//9-
void exit();

#endif

