#ifndef BLABLACAR_H
#define BLABLACAR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openssl/evp.h> //cryptage

typedef struct s_date Date;
typedef struct s_trajet Trajet;
typedef struct s_ville Ville;
typedef struct s_conducteur Conducteur;
typedef struct s_client Client;
typedef struct s_admin Admin;


// se renseiger sur l'export et le chiffrage ( pas sûr des classes à mettre dans ces cas là)
// détail du sujet pour l'heure :"On considérera que les trajets ne se déroulent qu’en journée" par ex, aucune horaire dans la liste horairendu trajet ne doit etre entre 22h et 6h ?

//----------tous---------
//0-
void login(Conducteur* conducteurs, Client* clients, Admin admin ); //conducteur : juste id ; client : id + mdp ; admin : un seul compte ( id: Titouan_le_boute_en_train ; mdp chiffré)
//9-
void exit();

//------------admin---------------
// 1- Gestion villes
void add_v(Ville* villes);
void edit_v(Ville* villes,Ville ville);
void sup_v(Ville* villes, Ville ville);
//2- Exportation 
void export_json(Conducteur* Concducteurs, Client* Clients, Trajet* trajets, Ville* villes , const char* chemin_pc); // une fonction par chaque liste à export/ import ? || est ce vraiment utile d'exporter des trajets/  villes/ clients ? (pas sur)
void import_json(Conducteur* Concducteur, Client* Clients, Trajet* trajets, Ville* villes, const char* chemin_pc); // faut-il fournir la taille pour l'import/l'export ?
//3- Admin  
void admin_mdp_conducteur(Conducteur* conducteurs, Conducteur conducteur);
void admin_mdp_client(Client* clients, Client client);

//-----------conducteur-------------

// 4 Créer Offre
void creer_trajet(Conducteur conducteur, Trajet* trajets, Ville* villes); // Conducteur* ou Conducteur ? Normalement le conducteur connecté est designé d'office || note : pour un trajet de plusieurs villes, horaire est une liste où l'element x appartient à l'horaire de départ de la x eme ville du trajet)
//5 Afficher tous les trajets du conducteur connecté
void afficher_trajets(Trajet* trajets, Conducteur conducteur); // Conducteur* ou Conducteur ?  mm raisonnement qu'au 4
//6 changer ses logs
void changer_logs_conducteur( Conducteur conducteur);  // besoin de conducteur* ? je dirais non || 1 fonction mdp et 1 fonction pseudo ou 1 pour les 2 ? 1 pour les 2 imo


//---------------clients------------------ ( obligation de faire 7 avant 8 ?)


//7-
void chercher_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs); // des doutes sur la date pour la recherche : demander juste jour ou aussi heure ? essayer de mettre une plage horaire plutot qu'une seule heure ,

//8-
void reserver_trajet(Trajet* trajets, Ville* villes, Conducteur* conducteurs, Client client); // on comprend ici que reservation et modification sont des synonymes. est ce juste ? ou y a t il 2 fonctions/actions distinctes ? || // (voir explication du 4) du coup dans la meme idée on a aussi le nombre de passagers sur chaque troncon 0,1 ou 2 ; (faut que le nombre de passagers s'update sur plusieurs troncon si le clients reste sur plusieurs troncons)

#endif

