

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <jansson.h>

typedef struct s_date* Date;
typedef struct s_trajet* Trajet;
typedef struct s_conducteur* Conducteur;
typedef struct s_client* Client;
typedef struct s_admin* Admin;
typedef struct s_troncon* Troncon ;

/////////////////ALLOC////////////////

Date allocDate(int anneeArg, int moisArg, int jourArg, int heureArg, int minutesArg);
Admin allocAdmin(const char* idArg, const char* mdpArg);
Conducteur allocConducteur(const char* idArg, const char* mdpArg);
Client allocClient(const char* idArg, const char* mdpArg);
Troncon allocTroncon(const char* arg_depart , const char* arg_arrive , Date datearg , const char** passagers);

Trajet allocTrajet( const char* conducteurArg, int nbvilles , Troncon* liste_tronc);
//---------------json-----------------
json_t* fonction_data_json(const char * chemin_json);
const char** Liste_jsonTostr(json_t* dataJson , const char* motclé);
int taille_liste_json(json_t* dataJson , const char * motclé);


//----------tous---------
void login(Conducteur* conducteurs, Client* clients, Admin admin);
void menu_admin(Admin admin,const char** villes, int *NB_villes,     const char** conds, int* NB_conds,const char ** mdpconds, Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);
void login_admin(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds, Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);
void login_conducteur(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds,Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);

int date_valide(int annee, int mois, int jour, int heure, int minute);

int ville_valide(const char** villes, int *NB_villes, char nom[50]);

void sup_v(const char** villes, int *NB_villes);
void add_v(const char** villes, int* NB_villes);

void edit_v(const char** villes, int* NB_villes);


void sup_c(const char** villes, int *NB_villes);
void add_c(const char** villes, int* NB_villes);

void edit_c(const char** villes, int* NB_villes);



void sup_MDPc(const char** villes, int *NB_villes);
void add_MDPc(const char** villes, int* NB_villes);
void edit_MDPc(const char** villes, int* NB_villes);

void menu_modif_cond(Admin admin,const char** conds, int* NB_conds   ,   const char** villes, int *NB_villes,  const char** mdpconds, Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);

void creer_trajet(const char* conducteur, const char** villes, int * NB_villes, Trajet* listetrajos, int* NB_trajets) ;
void export_liste(json_t* donnee,const char* nomTableau, char** listeChaine, int tailleListe,  const char * chemin_json);

void menuprincipal(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds, Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);

void afficher_trajets(Trajet* trajets, int *NB_trajets, const char* conducteur);
void reserver_trajet(Trajet* trajets, int* NB_trajets, const char** villes, const char* client);

void menu_client(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds, Trajet* trajets, int *NB_trajets , const char *client, const char** clients, int* NB_clients ,const char **MDPclients) ;
void login_client(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds, Trajet* trajets, int *NB_trajets , const char **clients, int *NB_clients,const char **MDPclients);

void afficher_tous_trajets(Trajet*trajets , const char** conds , int* NB_trajets, int* NB_conds);

void edit_cond(const char* conducteur , const char* mdp);
