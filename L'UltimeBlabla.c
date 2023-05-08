#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Blablacar.h"
#include <jansson.h>

///////STRUCT///////////

struct s_date {
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
};

struct s_admin {
    const char* id;
    const char* mdp;
};

struct s_conducteur {
    const char* id;
    const char* mdp;
};

struct s_client {
    const char* id;
    const char* mdp;
};
struct s_troncon{
    const char* ville_depart ;
    const char* ville_fin ;
    Date date_tronc ;
    const char** passagersId ;
};

struct s_trajet {
    Troncon* liste_tronc ;//[tronçon1 , troncon 2]
    const char * conducteur;
    int nbVilles;//taille liste troncon*2
};

//-------------------ALLOCATIONS---------------------------

Date allocDate(int anneeArg , int moisArg,int jourArg, int heureArg, int minutesArg){
    Date resultat = malloc(sizeof(struct s_date));
    resultat->annee = anneeArg;
    resultat->mois = moisArg ;
    resultat->jour = jourArg ;
    resultat->heure = heureArg ;
    resultat->minute = minutesArg ;
    return (resultat);
}

Admin allocAdmin(const char* idArg ,const char* mdpArg){
    Admin resultat = malloc(sizeof(struct s_admin));
    resultat->id = idArg ;
    resultat->mdp = mdpArg ;
    printf("Alloc admin OK\n\n");
    return (resultat);
}

Conducteur allocConducteur(const char* idArg, const char* mdpArg){
    Conducteur  res = malloc(sizeof(struct s_conducteur));
    res->id = idArg ;
    res->mdp = mdpArg ;
    return (res);
}

Client allocClient(const char* idArg1,const char* mdpArg1){
    Client  res1 = malloc(sizeof(struct s_client));
    res1->id = idArg1 ;
    res1->mdp = mdpArg1 ;
    return (res1);
}

Troncon allocTroncon(const char* villedeparg , const char* villeArrive , Date datetroncarg, const char ** idpassagers){
    Troncon res = malloc(sizeof(struct s_troncon));
    res->ville_depart = villedeparg ;
    res->ville_fin = villeArrive ;
    res->date_tronc = datetroncarg ;
    res->passagersId = idpassagers ;
    return (res);
}

Trajet allocTrajet( const char * conducteurArg, int nbvillesarg , Troncon* liste_troncarg){
    Trajet res = malloc(sizeof(struct s_trajet)) ;
    res-> liste_tronc = liste_troncarg ;
    res->conducteur = conducteurArg ;
    res->nbVilles = nbvillesarg ;
    return(res);
}

/////////////////Fonctions Json/////////////////////////////
//importe le json du chemin indiqué et renvoie les données de type json*
json_t* fonction_data_json(const char * chemin_json){
    //lecture du json:
    json_error_t erreur ;
    
    json_t *données_json ;
    //on met dans données les données du fichier json on met 0 en 2eme parametre pour les valeurs par defaut que proposes la lib
    données_json = json_load_file(chemin_json,0, &erreur);
    assert(données_json != NULL);//si il y a un probleme dans la lecture on veut que ça crash

    printf("Le json est bien chargé!!\n\n");
    return (données_json );   
}

const char** liste_jsonTostr(json_t* dataJson , const char* motclé){
    json_t* variable = json_object_get(dataJson,motclé)  ;  //mot clé testliste
    int taille_liste= json_array_size(variable);
    
    const char** liste_native = malloc(sizeof(char*) * taille_liste);

    // On vérifie que la liste a été correctement récupérée
    //assert(!json_is_array(testliste));
    //on remplie la liste c native avec les element du json

    for (int i=0; i<taille_liste; i++){

        json_t*element_json = json_array_get(variable,i);
        const char* element_jsonTostr = json_string_value(element_json);
        liste_native[i]=element_jsonTostr ;       
    }
    
    printf("La liste est bien convertie!!\n\n");
    return(liste_native);
}

int taille_liste_json(json_t* dataJson, const char* motclé){
    json_t* variable = json_object_get(dataJson,motclé)  ;  //mot clé testliste
    int taille_liste= json_array_size(variable);
    return (taille_liste);
}
/////////////////////////////


////////!!!!!!!!!!!!//////////Fonctions principales/////!!!!!!!!!!!!!////////////////

/////////////////////ADMIN////////////////////////////////////

void login_admin(Admin admin, const char** villes, int *NB_villes) {
    char ida[20];
    char mdpa[20];
    printf("Identifiant : ");
    scanf("%s", ida);
    printf("Mot de passe : ");
    scanf("%s", mdpa);   
    if (strcmp(admin->id, ida) == 0 && strcmp(admin->mdp, mdpa) == 0) {
        printf("Bienvenue %s !\n", admin->id);
        menu_admin(villes,NB_villes);//arg conducteurs, clients, trajets, villes
    } else {
        printf("Identifiant ou mot de passe incorrect\n");
        login_admin(admin,villes , NB_villes);
    }
}

void menu_admin(const char** villes, int *NB_villes) {//Conducteur* conducteurs, Client* clients, Trajet* trajets, const char** villes
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
    if (choix == 1){
        add_v(villes,NB_villes);
    }
    else if (choix == 8) {
        printf("Au revoir !\n");
        exit(0);
    }
    else {
        printf("Choix invalide\n");
        //conducteurs, clients, trajets, villes
    }
    menu_admin(villes,NB_villes);
}

//1
void add_v(const char** villes, int *NB_villes) {
    printf("Nom de la ville à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    villes[*NB_villes] = nom;
    printf("La ville %s a bien été ajoutée !\n", nom);
    (*NB_villes)++;   
}

//2
void edit_v(const char** villes, int* NB_villes) {
    printf("Nom de la ville à modidier : ");
    char nom[50];
    scanf("%s", nom);
    int found = 0;
    for (int i = 0; i < *NB_villes; i++) {
        if (strcmp(villes[i], nom) == 0) {
            for (int j = i; j < (*NB_villes) - 1; j++) {
                villes[j] = villes[j + 1];
            }
            found = 1;
            (*NB_villes)--;
            printf("Nouveau nom de ville : ");
            char nom[50];
            scanf("%s", nom);

            villes[*NB_villes] = nom;
            printf("La ville a bien ete modifiée en %s !\n", nom);
            (*NB_villes)++;
    
            break;
        }
    }
    if (!found) {
        printf("La ville %s n'a pas été trouvée\n", nom);
    }
}

//3
void sup_v(const char** villes, int* NB_villes){
    printf("Nom de la ville à supprimer : ");
    char nom[50];
    scanf("%s", nom);
    int found = 0;
    for (int i = 0; i < *NB_villes; i++) {
        if (strcmp(villes[i], nom) == 0) {
            for (int j = i; j < (*NB_villes) - 1; j++) {
                villes[j] = villes[j + 1];
            }
            found = 1;
            (*NB_villes)--;
            printf("La ville %s a été supprimée avec succès !\n", nom);
            break;
        }
    }
    if (!found) {
        printf("La ville %s n'a pas été trouvée\n", nom);
    }
}




//----------------MAIN---------------------

int main() {

    /////////////////Déclarations de Variables et Load//////////////////

    json_t * donnee_load = fonction_data_json("/home/olivier/CUPGEs1/tpbash/marchepas.json");



    ///////////////////////TAILLES///////////
    int taille_liste_ville_nat = taille_liste_json(donnee_load , "villes");
    

    ////////////admin///////////



    const char* admin_id = liste_jsonTostr(donnee_load , "id_admin")[0];
    const char* admin_mdp = liste_jsonTostr(donnee_load , "mdp_admin")[0];
    //////////////listes//////
    /*const char** liste_conducteurs_main = liste_jsonTostr(donnee_load,"conducteurs");
    const char** liste_mdp_conducteurs_main = liste_jsonTostr(donnee_load,"mdp_conducteurs");
    //////////////////////*/

    const char** villes = liste_jsonTostr(donnee_load, "villes");
    /*
    const char ** liste_clients_main = liste_jsonTostr(donnee_load,"clients");
    const char ** liste_mdp_clients_main = liste_jsonTostr(donnee_load,"mdp_clients");


    ////////////////TEST//////////*/
    
    


    //////////

    

    Admin philippe = allocAdmin(admin_id , admin_mdp);
    
    
    
    


    /////////////////Main//////////////////

    int choix;
    printf("Voulez-vous vous connecter en tant que : \n");
    printf("1- Administrateur\n");
    printf("2- Conducteur\n");
    printf("3- CLient\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        login_admin(philippe,villes,&taille_liste_ville_nat);
    }
    
    else if (choix == 4) {
        printf("Au revoir !\n");
        exit(0);
    }
    
    
    printf("yo\n");

    printf("test taille l villes : %d\n\n", taille_liste_ville_nat);
    add_v(villes , &taille_liste_ville_nat);

    sup_v(villes, &taille_liste_ville_nat);
    edit_v(villes , &taille_liste_ville_nat);

    printf("test : %d\n", taille_liste_ville_nat);
    return 0 ;
    
}
