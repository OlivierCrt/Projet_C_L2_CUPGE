

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
void menu_admin(const char** villes, int *NB_villes);
void login_admin(Admin admin, const char** villes, int *NB_villes);

void sup_v(const char** villes, int *NB_villes);
void add_v(const char** villes, int* NB_villes);

