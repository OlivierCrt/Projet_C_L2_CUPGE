#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Blablacar.h"
#include <jansson.h>


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


//////////////////Fonctions principales/////////////////////

void login_admin(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds) {
    char ida[20];
    char mdpa[20];
    char newa[20];
    printf("Identifiant : ");
    scanf("%s", ida);
    printf("Mot de passe : ");
    scanf("%s", mdpa);
    cryptageV2(mdpa,5,newa);
    
    if (strcmp(admin->id, ida) == 0 && strcmp(admin->mdp, newa) == 0) {
        printf("Bienvenue %s !\n", admin->id);
        menu_admin(villes,NB_villes , conds , NB_conds, mdpconds);//arg conducteurs, clients, trajets, villes
    } else {
        printf("Identifiant ou mot de passe incorrect\n");
        login_admin(admin,villes , NB_villes  ,conds , NB_conds, mdpconds);
    }
}

void menu_admin(const char** villes, int *NB_villes,     const char** conds, int* NB_conds,const char ** mdpconds) {//Conducteur* conducteurs, Client* clients, Trajet* trajets, const char** villes
    int choix;
    printf("Vous voulez : \n");
    printf("1- Ajouter une ville\n");
    printf("2- Modifier une ville\n");
    printf("3- Supprimer une ville\n");
    //printf("4- Exporter un JSON\n");
    //printf("5- Importer un JSON\n");
    printf("4- Modifier le profil d'un conducteur\n");
    printf("5- Modifier le mdp d'un client\n");
    printf("6- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1){
        add_v(villes,NB_villes);
    }
    else if (choix == 2){
        edit_v(villes,NB_villes);
    }
    else if(choix == 3){
        sup_v(villes, NB_villes);
    }
    else if(choix == 4){
        menu_modif_cond(conds,NB_conds   ,   villes, NB_villes, mdpconds);
    }
    else if (choix == 6) {
        printf("Au revoir !\n");
        exit(0);
    }
    else {
        printf("Choix invalide\n");
        //conducteurs, clients, trajets, villes
    }
    menu_admin(villes,NB_villes  , conds , NB_conds, mdpconds);
}

void login_conducteur(Admin admin, const char** villes, int *NB_villes , const char** conds , int* NB_conds, const char** mdpconds){
    char idcond[20] ;
    char mdPcond[20] ;
    char newc[20];
    printf("Identifiant : ");
    scanf("%s", idcond);
    printf("Mot de passe : ");
    scanf("%s", mdPcond);
    cryptageV2(mdPcond,5,newc);
    printf("okok\n");

    for (int i = 0;i<*NB_conds ; i++){
        
        if (strcmp(conds[i],idcond) == 0){

            for (int u = 0 ; u<*NB_conds ; u++){
                if (strcmp(mdpconds[i],newc) == 0){
                    
                    menu_modif_cond(conds, NB_conds   ,   villes, NB_villes, mdpconds);

                     }

             }
        }
        

    }


}

/////////////////////////DATE//////////////////

int date_valide(int annee, int mois, int jour, int heure, int minute) { // 1 si ok, 0 si pas ok
    int ok = 1;
    int jours_par_mois[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        jours_par_mois[2] = 29;
    }
    if (annee < 2000 || annee>2100) {
        printf("Année inexistante");
        ok = 0;
    }
    if (mois < 1 || mois > 12) {
        printf("mois inexistant");
        ok = 0;
    }
    if (jour < 1 || jour > jours_par_mois[mois]) {
        printf("jour inexistant");
        ok = 0;
    }
    if (heure < 0 || heure > 23) {
        printf("heure inexistante");
        ok = 0;
    }
    if (minute < 0 || minute > 59) {
        printf("minute inexistante");
        ok = 0;
    }
    return ok;
}

int ville_valide(const char** villes, int * NB_villes, char nom[50]) { //1 si ok, 0 si pas ok
    int found = 0;
    for (int i = 0; i < *NB_villes; i++) {
        if (strcmp(villes[i], nom) == 0) {
            for (int j = i; j < (*NB_villes) - 1; j++) {
                villes[j] = villes[j + 1];
            }
            found = 1;
        }
    }
    if (!found) {
        printf("La ville %s n'a pas été trouvée\n", nom);
    }
    return found;
}






///////////////////////////Villes///////////////////////////////

void add_v(const char** villes, int *NB_villes) {
    printf("Nom de la ville à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    villes[*NB_villes] = nom;
    printf("La ville %s a bien été ajoutée !\n", nom);
    (*NB_villes)++;
    
    
}
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
////////////////////////////Conducteurs///////////////////////////
void add_IDc(const char**lconducteurs , int * NB_conducteurs){
    printf("Nom du conducteur à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    lconducteurs[*NB_conducteurs] = nom;
    printf("Le conducteur %s a bien été ajoutée !\n", nom);
    (*NB_conducteurs)++;

}

void edit_IDc(const char** villes, int* NB_villes) {//changer les noms de var après
    printf("Id du conducteur à modidier : ");
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
            printf("Nouveau ID : ");
            char nom[50];
            scanf("%s", nom);

            villes[*NB_villes] = nom;
            printf("L ID a bien ete modifiée en %s !\n", nom);
            (*NB_villes)++;
    
            break;
        }
    }
    if (!found) {
        printf("L'ID %s n'a pas été trouvé\n", nom);
    }
}

void sup_IDc(const char** villes, int* NB_villes){
    printf("Id du conducteur à supprimer : ");
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
            printf("L'Id %s a été supprimé avec succès !\n", nom);
            break;
        }
    }
    if (!found) {
        printf("L'ID' %s n'a pas été trouvé\n", nom);
    }
}
   
void menu_modif_cond(const char** conds, int* NB_conds   ,   const char** villes, int *NB_villes,  const char** mdpconds){
    int choix ;
    printf("Vous voulez :\n");
    printf("1- ajouter ID conducteur\n");
    printf("2- modifier ID conducteur\n");
    printf("3- supprimer ID conducteur\n");
    printf("4- ajouter MDP conducteur\n");
    printf("5- modifier MDP conducteur\n");
    printf("6- supprimer MDP conducteur\n");
    printf("7- revenir au menu précédent\n");
    scanf("%d", &choix);
    if(choix == 1){
        add_IDc(conds , NB_conds);
    }
    else if(choix == 2){
        edit_IDc(conds , NB_conds);
    }
    else if(choix == 3){
        sup_IDc(conds , NB_conds);
    }
    else if(choix == 4){
        add_MDPc(mdpconds , NB_conds);
    }
    else if(choix == 5){
        edit_MDPc(mdpconds , NB_conds);
    }
    else if(choix == 6){
        sup_MDPc(mdpconds , NB_conds);
    }
    else if(choix == 7){
        menu_admin(villes,NB_villes , conds , NB_conds, mdpconds );

    }
    else {
        printf("Choix invalide\n");
        //conducteurs, clients, trajets, villes
    }
    menu_modif_cond(conds,NB_conds , villes , NB_villes,mdpconds);


}
/////////////////////////////clients///////////

void add_MDPc(const char**lconducteurs , int * NB_conducteurs){
    printf("mot de passe à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    lconducteurs[*NB_conducteurs] = nom;
    printf("Le MDP %s a bien été ajouté !\n", nom);
    (*NB_conducteurs)++;

}

void edit_MDPc(const char** villes, int* NB_villes) {//changer les noms de var après
    printf("MDP  à modidier : ");
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
            printf("Nouveau MDP : ");
            char nom[50];
            scanf("%s", nom);

            villes[*NB_villes] = nom;
            printf("Le MDP a bien ete modifiée en %s !\n", nom);
            (*NB_villes)++;
    
            break;
        }
    }
    if (!found) {
        printf("Le MDP %s n'a pas été trouvé\n", nom);
    }
}

void sup_MDPc(const char** villes, int* NB_villes){
    printf("MDP du conducteur à supprimer : ");
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
            printf("LE MDP %s a été supprimé avec succès !\n", nom);
            break;
        }
    }
    if (!found) {
        printf("Le MDP %s n'a pas été trouvé\n", nom);
    }
}
   
/////////////////////TRAJET/////////////

void creer_trajet(const char* conducteur, const char** villes, int * NB_villes) {
    printf("Vous allez créer un trajet. Lors de la saisie assurez vous de n'entrer que des noms de villes desservies.\nDe plus votre trajet ne peut se dérouler sur plusieurs jours.\n\n");
    int date_ok = 0;
    const char * listeclient[50] ;
    int an;
    int mo;
    int jo;
    int he;
    int mi;

    Date * liste_date = malloc(sizeof(Date));
    Troncon * liste_tronc = malloc(sizeof(Troncon)) ;

    //premiere ville
    while (date_ok == 0) {
        
        printf("Entrez la date de votre départ :\n");
        printf("L'année de départ :");
        
        scanf("%d", &an);

        printf("Le mois de départ (entre 1 et 12) :");
        
        scanf("%d", &mo);

        printf("Le jour de départ (entre 1 et 31) :");
        
        scanf("%d", &jo);
        
        
        date_ok = 1;
        int jours_par_mois[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((an % 4 == 0 && an % 100 != 0) || an % 400 == 0) {
            jours_par_mois[2] = 29;
        }
        if (an < 2000 || an>2100) {
            printf("Année inexistante");
            date_ok = 0;
        }
        if (mo < 1 || mo > 12) {
            printf("mois inexistant");
            date_ok = 0;
        }
        if (jo < 1 || jo > jours_par_mois[mo]) {
            printf("jour inexistant");
            date_ok = 0;
        }
        
        if (date_ok == 0) {
            printf("Erreur de saisie dans la date. Vérifiez que la date saisie existe\n");
        }


    }


    int nb_v = 0; //nb ville
    while (nb_v <= 0) {
        printf("Entrez le nombre de villes par lesquelles vous allez passer ( en comptant le départ ) : ");
        scanf("%d", &nb_v);
        if (nb_v <= 0) {
            printf("Erreur de saisie");
        }
    }

    int dep_ok = 0;//test villeok
    char v_dep[50];
    //entrer ville dep
    while (dep_ok == 0) {
        printf("Entrez le nom de la ville de départ");
        scanf("%s", v_dep);
        dep_ok = ville_valide(villes, NB_villes, v_dep);
        if (dep_ok == 0) {
            printf("Ville inexistante");
        }
    }//v_dep definie

    
    for (int i = 0; i < (nb_v - 1); i++) {
        liste_tronc[i] = malloc(sizeof(struct s_troncon));
        liste_date[i] = malloc(sizeof(struct s_date));
        int date_ok = 0;

        //DATE DE DEP TRONCON
        while (date_ok == 0) {
            printf("Entrez l'heure à laquelle vous partirez de %s :\n", v_dep);
            printf("L'heure (entre 8 et 20) :");
            scanf("%d", &he);

            printf("Les minutes(entre 0 et 59) : ");
            scanf("%d", &mi);
            
            date_ok = date_valide(an, mo, jo, he, mi);
            if (date_ok == 0) {
                printf("Erreur de saisie dans la date. Vérifiez que la date saisie existe\n");
            }
        }
        
        int fin_ok = 0;
        char v_fin[50];
        //definition vfin troncon
        while (fin_ok == 0) {
            printf("Entrez le nom de la ville suivante");
            scanf("%s", v_fin);
            fin_ok = ville_valide(villes,NB_villes, v_fin);
            if (fin_ok == 0) {
                printf("Ville inexistante");
            }
        }//vfin definie


       








        liste_tronc[i]->ville_depart = v_dep;
        liste_tronc[i]->ville_fin = v_fin;
        liste_tronc[i]->date_tronc = liste_date[i];
        liste_tronc[i]->passagersId = listeclient;
        strcpy(v_dep, v_fin);

    }

    Trajet trajet = allocTrajet(  conducteur , nb_v, liste_tronc );

    printf("%d", trajet->nbVilles);
}










//----------------MAIN---------------------

int main() {

    /////////////////Déclarations de Variables et Load//////////////////

    json_t * donnee_load = fonction_data_json("/home/olivier/CUPGEs1/tpbash/marchepas.json");



    ///////////////////////TAILLES///////////
    int taille_liste_ville_nat = taille_liste_json(donnee_load , "villes");
    int taille_liste_conducteurs_nat = taille_liste_json(donnee_load , "conducteurs");
    

    ////////////admin//////x/////



    const char* admin_id = liste_jsonTostr(donnee_load , "id_admin")[0];
    const char* admin_mdp = liste_jsonTostr(donnee_load , "mdp_admin")[0];
    //////////////listes//////
    const char** conds = liste_jsonTostr(donnee_load,"conducteurs");
    const char** mdpconds = liste_jsonTostr(donnee_load,"mdp_conducteurs");
    //////////////////////*/

    const char** villes = liste_jsonTostr(donnee_load, "villes");
    /*
    const char ** liste_clients_main = liste_jsonTostr(donnee_load,"clients");
    const char ** liste_mdp_clients_main = liste_jsonTostr(donnee_load,"mdp_clients");


    ////////////////TEST//////////*/
    
    


    //////////

    

    Admin philippe = allocAdmin(admin_id , admin_mdp);
    
    
    
    


    /////////////////Main//////////////////
    creer_trajet(conds[0] , villes , &taille_liste_ville_nat) ;
    printf("OK   <qsldejfheq:kfug \n\n\n") ;
    int choix;
    printf("Voulez-vous vous connecter en tant que : \n");
    printf("1- Administrateur\n");
    printf("2- Conducteur\n");
    printf("3- CLient\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        login_admin(philippe,villes,&taille_liste_ville_nat   , conds , &taille_liste_conducteurs_nat , mdpconds);
    }
    else if (choix == 2){
        login_conducteur(philippe,villes,&taille_liste_ville_nat   , conds , &taille_liste_conducteurs_nat , mdpconds);
    }
    
    else if (choix == 4) {
        printf("Au revoir !\n");
        exit(0);
    }
    
    
    printf("yo\n");

    
    return 0 ;
    
}
