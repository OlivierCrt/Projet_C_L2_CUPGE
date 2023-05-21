/**
 * @file upssivroum.c
 * @brief Programme permettant de gérer une entreprise de Covoiturage
 * @author Solal Danton Laloy
 *         Olivier Crampette
 *         Romain Pezet
 * @date Date de création du fichier
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Blablacar.h"
#include <jansson.h>


struct s_date {
    int annee; /**< Année */
    int mois; /**< Mois */
    int jour; /**< Jour */
    int heure; /**< Heure */
    int minute; /**< Minute */
};

struct s_admin {
    const char* id; /**< Identifiant de l'administrateur */
    const char* mdp; /**< Mot de passe de l'administrateur */
};


struct s_conducteur {
    const char* id; /**< Identifiant du conducteur */
    const char* mdp; /**< Mot de passe du conducteur */
};

struct s_client {
    const char* id; /**< Identifiant du client */
    const char* mdp; /**< Mot de passe du client */
};

struct s_troncon {
    const char* ville_depart; /**< Ville de départ du tronçon */
    const char* ville_fin; /**< Ville de fin du tronçon */
    Date date_tronc; /**< Date du tronçon */
    const char** passagersId; /**< Identifiants des passagers du tronçon */
};

struct s_trajet {
    Troncon* liste_tronc; /**< Liste des tronçons du trajet */
    const char* conducteur; /**< Identifiant du conducteur */
    int nbVilles; /**< Nombre de villes dans le trajet */
};

//-------------------ALLOCATIONS---------------------------

/**
 * @brief Alloue et crée une structure de type Date.
 * @param anneeArg Année de la date
 * @param moisArg Mois de la date
 * @param jourArg Jour de la date
 * @param heureArg Heure de la date
 * @param minutesArg Minutes de la date
 * @return Pointeur vers la structure Date allouée
 */
Date allocDate(int anneeArg, int moisArg, int jourArg, int heureArg, int minutesArg) {
    Date resultat = malloc(sizeof(struct s_date));
    resultat->annee = anneeArg;
    resultat->mois = moisArg;
    resultat->jour = jourArg;
    resultat->heure = heureArg;
    resultat->minute = minutesArg;
    return (resultat);
}

/**
 * @brief Alloue et crée une structure de type Admin.
 * @param idArg Identifiant de l'administrateur
 * @param mdpArg Mot de passe de l'administrateur
 * @return Pointeur vers la structure Admin allouée
 */
Admin allocAdmin(const char* idArg, const char* mdpArg) {
    Admin resultat = malloc(sizeof(struct s_admin));
    resultat->id = idArg;
    resultat->mdp = mdpArg;
    return (resultat);
}

/**
 * @brief Alloue et crée une structure de type Conducteur.
 * @param idArg Identifiant du conducteur
 * @param mdpArg Mot de passe du conducteur
 * @return Pointeur vers la structure Conducteur allouée
 */
Conducteur allocConducteur(const char* idArg, const char* mdpArg) {
    Conducteur res = malloc(sizeof(struct s_conducteur));
    res->id = idArg;
    res->mdp = mdpArg;
    return res;
}

/**
 * @brief Alloue et crée une structure de type Client.
 * @param idArg Identifiant du client
 * @param mdpArg Mot de passe du client
 * @return Pointeur vers la structure Client allouée
 */
Client allocClient(const char* idArg, const char* mdpArg) {
    Client res = malloc(sizeof(struct s_client));
    res->id = idArg;
    res->mdp = mdpArg;
    return res;
}

/**
 * @brief Alloue et crée une structure de type Troncon.
 * @param villeDepartArg Ville de départ du tronçon
 * @param villeFinArg Ville de fin du tronçon
 * @param dateArg Date du tronçon
 * @param passagersIdArg Identifiants des passagers du tronçon
 * @return Pointeur vers la structure Troncon allouée
 */
Troncon allocTroncon(const char* villeDepartArg, const char* villeFinArg, Date dateArg, const char** passagersIdArg) {
    Troncon res = malloc(sizeof(struct s_troncon));
    res->ville_depart = villeDepartArg;
    res->ville_fin = villeFinArg;
    res->date_tronc = dateArg;
    res->passagersId = passagersIdArg;
    return res;
}

/**
 * @brief Alloue et crée une structure de type Trajet.
 * @param listeTroncArg Liste des tronçons du trajet
 * @param conducteurArg Identifiant du conducteur
 * @param nbVillesArg Nombre de villes dans le trajet
 * @return Pointeur vers la structure Trajet allouée
 */
Trajet allocTrajet(Troncon* listeTroncArg, const char* conducteurArg, int nbVillesArg) {
    Trajet res = malloc(sizeof(struct s_trajet));
    res->liste_tronc = listeTroncArg;
    res->conducteur = conducteurArg;
    res->nbVilles = nbVillesArg;
    return res;
}

/////////////////////TRAJET////////////////////


/**
 * @brief Importe le fichier JSON à partir du chemin spécifié et renvoie les données de type json_t*.
 *
 * @param chemin_json Le chemin du fichier JSON à importer.
 * @return Les données JSON importées.
 */
json_t* fonction_data_json(const char* chemin_json) {
    //lecture du json:
    json_error_t erreur;

    json_t* données_json;
    //on met dans données les données du fichier json on met 0 en 2eme parametre pour les valeurs par defaut que proposes la lib
    données_json = json_load_file(chemin_json, 0, &erreur);
    assert(données_json != NULL);//si il y a un probleme dans la lecture on veut que ça crash

    printf("Le json est bien chargé!!\n\n");
    return (données_json);
}


/**
 * @brief Prends les chaines de caractères dans le json et les mets dans des listes C
 *
 * @param dataJson Le JSON contenant les données.
 * @param motclé Le mot-clé correspondant aux chaînes de caractères dans le JSON.
 * @return Les chaînes de caractères converties en listes C.
 */
const char** liste_jsonTostr(json_t* dataJson, const char* motclé) {
    json_t* variable = json_object_get(dataJson, motclé);  //mot clé testliste
    int taille_liste = json_array_size(variable);

    const char** liste_native = malloc(sizeof(char*) * taille_liste);

    // On vérifie que la liste a été correctement récupérée
    //assert(!json_is_array(testliste));
    //on remplie la liste c native avec les element du json

    for (int i = 0; i < taille_liste; i++) {
        json_t* element_json = json_array_get(variable, i);
        const char* element_jsonTostr = json_string_value(element_json);
        liste_native[i] = element_jsonTostr;
    }
    return(liste_native);
}

/**
 * @brief Renvoie la taille d'une liste dans le JSON spécifié par le mot-clé.
 *
 * @param dataJson Le JSON contenant les données.
 * @param motclé Le mot-clé correspondant à la liste dans le JSON.
 * @return La taille de la liste dans le JSON.
 */
int taille_liste_json(json_t* dataJson, const char* motclé) {
    json_t* variable = json_object_get(dataJson, motclé);  //mot clé testliste
    int taille_liste = json_array_size(variable);
    return (taille_liste);
}

/**
 * @brief Exporte une liste de chaînes de caractères dans le fichier JSON au mot-clé spécifié.
 *
 * @param donnee Le JSON dans lequel exporter les données.
 * @param nomTableau Le nom du tableau correspondant au mot-clé dans le JSON.
 * @param listeChaine La liste de chaînes de caractères à exporter.
 * @param tailleListe La taille de la liste à exporter.
 * @param chemin_json Le chemin du fichier JSON dans lequel exporter les données.
 */

//export d une liste de cconst char* dans le json
//donnee : json importé précedement , nomTableau motclé correspondant , listeChaine la liste de nom
//export_liste permet d'exporter une liste de const char * dans le fichier json au mot clé spécifié

void export_liste(json_t* donnee, const char* nomTableau, char** listeChaine, int tailleListe, const char* chemin_json) {
    json_t* tableau = json_object_get(donnee, nomTableau); // Récupération du tableau correspondant
    if (!tableau || !json_is_array(tableau)) {
        fprintf(stderr, "Erreur: Impossible de récupérer le tableau %s.\n", nomTableau);
        return;
    }

    for (int i = 0; i < tailleListe; i++) { // Ajout des chaînes de caractères dans le tableau
        json_array_append_new(tableau, json_string(listeChaine[i]));
    }

    int ecriture = json_dump_file(donnee, chemin_json, JSON_INDENT(2)); // Écriture du résultat dans le fichier JSON
    if (ecriture != 0) {
        fprintf(stderr, "Erreur: Impossible d'écrire dans le fichier JSON.\n");
    }
}
    
/////////////////////////////MENU principal//////////////////


/**
 * @brief Fonction principale du menu.
 *
 * @param admin L'objet Admin.
 * @param villes Les villes en tant que tableau de chaînes de caractères.
 * @param NB_villes Le nombre de villes.
 * @param conds Les conducteurs en tant que tableau de chaînes de caractères.
 * @param NB_conds Le nombre de conducteurs.
 * @param mdpconds Les mots de passe des conducteurs en tant que tableau de chaînes de caractères.
 * @param trajets Les trajets en tant que tableau de structures Trajet.
 * @param NB_trajets Le nombre de trajets.
 * @param clients Les clients en tant que tableau de chaînes de caractères.
 * @param NB_clients Le nombre de clients.
 * @param MDPclients Les mots de passe des clients en tant que tableau de chaînes de caractères.
 */
void menuprincipal(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    int choix;
    printf("Voulez-vous vous connecter en tant que : \n");
    printf("1- Administrateur\n");
    printf("2- Conducteur\n");
    printf("3- CLient\n");
    printf("4- Quitter le programme\n");
    scanf("%d", &choix);
    if (choix == 1) {
        login_admin(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
    else if (choix == 2) {
        login_conducteur(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
    else if (choix == 3) {
        login_client(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }

    else if (choix == 4) {
        printf("Au revoir !\n");
        exit(0);
    }
}

/**
 * @brief Fonction permettant de connecter un administrateur.
 *
 * @param admin L'administrateur à connecter.
 * @param villes La liste des villes.
 * @param NB_villes Le nombre de villes.
 * @param conds La liste des conducteurs.
 * @param NB_conds Le nombre de conducteurs.
 * @param mdpconds La liste des mots de passe des conducteurs.
 * @param trajets La liste des trajets.
 * @param NB_trajets Le nombre de trajets.
 * @param clients La liste des clients.
 * @param NB_clients Le nombre de clients.
 * @param MDPclients La liste des mots de passe des clients.
 */
void login_admin(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    char ida[20];
    char mdpa[20];
    printf("Identifiant : ");
    scanf("%s", ida);
    printf("Mot de passe : ");
    scanf("%s", mdpa);

    if (strcmp(admin->id, ida) == 0 && strcmp(admin->mdp, mdpa) == 0) {
        printf("Bienvenue %s !\n", admin->id);
        menu_admin(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);//arg conducteurs, clients, trajets, villes
    }
    else {
        printf("Identifiant ou mot de passe incorrect\n");
        login_admin(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
}

/**
 * @brief Fonction affichant le menu principal de l'administrateur.
 *
 * @param admin L'administrateur connecté.
 * @param villes La liste des villes.
 * @param NB_villes Le nombre de villes.
 * @param conds La liste des conducteurs.
 * @param NB_conds Le nombre de conducteurs.
 * @param mdpconds La liste des mots de passe des conducteurs.
 * @param trajets La liste des trajets.
 * @param NB_trajets Le nombre de trajets.
 * @param clients La liste des clients.
 * @param NB_clients Le nombre de clients.
 * @param MDPclients La liste des mots de passe des clients.
 */

void menu_admin(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    int choix;
    printf("Vous voulez : \n");
    printf("1- Ajouter une ville\n");
    printf("2- Modifier une ville\n");
    printf("3- Supprimer une ville\n");
    //printf("4- Exporter un JSON\n");
    //printf("5- Importer un JSON\n");
    printf("4- Menu conducteur\n");
    printf("5- Revenir au menu précedent\n");
    scanf("%d", &choix);
    if (choix == 1) {
        add_v(villes, NB_villes);
    }
    else if (choix == 2) {
        edit_v(villes, NB_villes);
    }
    else if (choix == 3) {
        sup_v(villes, NB_villes);
    }
    else if (choix == 4) {
        menu_modif_cond(admin, conds, NB_conds, villes, NB_villes, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }

    else if (choix == 5) {
        menuprincipal(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
    else {
        printf("Choix invalide\n");
        //conducteurs, clients, trajets, villes
    }
    menu_admin(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);

}

/**
 * @brief Fonction permettant de connecter un conducteur.
 *
 * @param admin L'administrateur.
 * @param villes La liste des villes.
 * @param NB_villes Le nombre de villes.
 * @param conds La liste des conducteurs.
 * @param NB_conds Le nombre de conducteurs.
 * @param mdpconds La liste des mots de passe des conducteurs.
 * @param trajets La liste des trajets.
 * @param NB_trajets Le nombre de trajets.
 * @param clients La liste des clients.
 * @param NB_clients Le nombre de clients.
 * @param MDPclients La liste des mots de passe des clients.
 */
void login_conducteur(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    char idcond[20];
    char mdPcond[20];
    printf("Identifiant : ");
    scanf("%s", idcond);
    printf("Mot de passe : ");
    scanf("%s", mdPcond);
    printf("okok\n");

    for (int i = 0; i < *NB_conds; i++) {

        if (strcmp(conds[i], idcond) == 0) {

            for (int u = 0; u < *NB_conds; u++) {
                if (strcmp(mdpconds[i], mdPcond) == 0) {

                    menu_modif_cond(admin, conds, NB_conds, villes, NB_villes, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);

                }

            }
        }
    }
}


//////////////////VALIDITE/////////////////////

/**
 * Vérifie si une date est valide.
 *
 * @param annee   L'année de la date.
 * @param mois    Le mois de la date.
 * @param jour    Le jour de la date.
 * @param heure   L'heure de la date.
 * @param minute  La minute de la date.
 *
 * @return 1 si la date est valide, 0 sinon.
 */
int date_valide(int annee, int mois, int jour, int heure, int minute) {
    int ok = 1;
    int jours_par_mois[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        jours_par_mois[2] = 29;
    }
    if (annee < 2000 || annee > 2100) {
        printf("Année inexistante");
        ok = 0;
    }
    if (mois < 1 || mois > 12) {
        printf("Mois inexistant");
        ok = 0;
    }
    if (jour < 1 || jour > jours_par_mois[mois]) {
        printf("Jour inexistant");
        ok = 0;
    }
    if (heure < 0 || heure > 23) {
        printf("Heure inexistante");
        ok = 0;
    }
    if (minute < 0 || minute > 59) {
        printf("Minute inexistante");
        ok = 0;
    }
    return ok;
}

/**
 * Vérifie si une ville est valide et la supprime de la liste des villes.
 *
 * @param villes      Le tableau de pointeurs vers les villes.
 * @param NB_villes   Le nombre de villes dans le tableau.
 * @param nom         Le nom de la ville à vérifier et supprimer.
 *
 * @return 1 si la ville est valide et supprimée, 0 sinon.
 */
int ville_valide(const char** villes, int* NB_villes, char nom[50]) {
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

/**
 * @brief Ajoute une nouvelle ville à la liste des villes.
 *
 * @param[in] villes Liste des villes existantes.
 * @param[in,out] NB_villes Pointeur vers le nombre de villes existantes.
 */
void add_v(const char** villes, int* NB_villes) {
    printf("Nom de la ville à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    villes[*NB_villes] = nom;
    printf("La ville %s a bien été ajoutée !\n", nom);
    (*NB_villes)++;
}

/**
 * @brief Modifie le nom d'une ville existante.
 *
 * @param[in] villes Liste des villes existantes.
 * @param[in,out] NB_villes Pointeur vers le nombre de villes existantes.
 */
void edit_v(const char** villes, int* NB_villes) {
    printf("Nom de la ville à modifier : ");
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
            printf("La ville a bien été modifiée en %s !\n", nom);
            (*NB_villes)++;

            break;
        }
    }
    if (!found) {
        printf("La ville %s n'a pas été trouvée\n", nom);
    }
}

/**
 * @brief Supprime une ville de la liste des villes.
 *
 * @param[in] villes Liste des villes existantes.
 * @param[in,out] NB_villes Pointeur vers le nombre de villes existantes.
 */
void sup_v(const char** villes, int* NB_villes) {
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


/////////////////////////////MDP conds-clients///////////

/**
 * @brief Ajoute un nouveau mot de passe de conducteur à la liste des mots de passe.
 *
 * @param[in] lconducteurs Liste des mots de passe de conducteurs existants.
 * @param[in,out] NB_conducteurs Pointeur vers le nombre de mots de passe de conducteurs existants.
 */
void add_MDPc(const char** lconducteurs, int* NB_conducteurs) {
    printf("mot de passe à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    lconducteurs[*NB_conducteurs] = nom;
    printf("Le MDP %s a bien été ajouté !\n", nom);
    (*NB_conducteurs)++;
}

/**
 * @brief Modifie un mot de passe de conducteur dans la liste des mots de passe.
 *
 * @param[in] villes Liste des mots de passe de conducteurs existants.
 * @param[in] NB_villes Pointeur vers le nombre de mots de passe de conducteurs existants.
 */
void edit_MDPc(const char** villes, int* NB_villes) {
    printf("MDP à modifier : ");
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
            printf("Le MDP a bien été modifié en %s !\n", nom);
            (*NB_villes)++;

            break;
        }
    }
    if (!found) {
        printf("Le MDP %s n'a pas été trouvé\n", nom);
    }
}

/**
 * @brief Supprime un mot de passe de conducteur de la liste des mots de passe.
 *
 * @param[in] villes Liste des mots de passe de conducteurs existants.
 * @param[in,out] NB_villes Pointeur vers le nombre de mots de passe de conducteurs existants.
 */
void sup_MDPc(const char** villes, int* NB_villes) {
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
            printf("Le MDP %s a été supprimé avec succès !\n", nom);
            break;
        }
    }
    if (!found) {
        printf("Le MDP %s n'a pas été trouvé\n", nom);
    }
}

////////////////////////////Modif Conducteurs///////////////////////////


/**
 * @brief Gère le menu de modification des conducteurs.
 *
 * @param[in] admin L'administrateur.
 * @param[in] conds Liste des ID de conducteurs existants.
 * @param[in,out] NB_conds Pointeur vers le nombre d'ID de conducteurs existants.
 * @param[in] villes Liste des villes existantes.
 * @param[in] NB_villes Pointeur vers le nombre de villes existantes.
 * @param[in] mdpconds Liste des mots de passe des conducteurs existants.
 * @param[in] trajets Liste des trajets existants.
 * @param[in] NB_trajets Pointeur vers le nombre de trajets existants.
 * @param[in] clients Liste des ID de clients existants.
 * @param[in] NB_clients Pointeur vers le nombre d'ID de clients existants.
 * @param[in] MDPclients Liste des mots de passe des clients existants.
 */
void menu_modif_cond(Admin admin, const char** conds, int* NB_conds, const char** villes, int* NB_villes, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    int choix;
    printf("Vous voulez :\n");
    printf("1- ajouter ID conducteur\n");
    printf("2- modifier ID conducteur\n");
    printf("3- supprimer ID conducteur\n");
    printf("4- ajouter MDP conducteur\n");
    printf("5- modifier MDP conducteur\n");
    printf("6- supprimer MDP conducteur\n");
    printf("7- Créer trajet \n");
    printf("8- revenir au menu précédent\n");
    scanf("%d", &choix);
    if (choix == 1) {
        add_IDc(conds, NB_conds);
    }
    else if (choix == 2) {
        edit_IDc(conds, NB_conds);
    }
    else if (choix == 3) {
        sup_IDc(conds, NB_conds);
    }
    else if (choix == 4) {
        add_MDPc(mdpconds, NB_conds);
    }
    else if (choix == 5) {
        edit_MDPc(mdpconds, NB_conds);
    }
    else if (choix == 6) {
        sup_MDPc(mdpconds, NB_conds);
    }
    else if (choix == 7) {
        creer_trajet(conds[0], villes, NB_villes, trajets, NB_trajets);
    }
    else if (choix == 8) {
        menu_admin(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
    else {
        printf("Choix invalide\n");
    }
    menu_modif_cond(admin, conds, NB_conds, villes, NB_villes, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
}


//////////////////////////Fonctions ID clients-cond  ///////////////////////////////

/**
 * @brief Ajoute un nouveau ID de conducteur à la liste des ID existants.
 *
 * @param[in] lconducteurs Liste des ID de conducteurs existants.
 * @param[in,out] NB_conducteurs Pointeur vers le nombre d'ID de conducteurs existants.
 */
void add_IDc(const char** lconducteurs, int* NB_conducteurs) {
    printf("Nom du conducteur à ajouter : ");
    char nom[50];
    scanf("%s", nom);

    lconducteurs[*NB_conducteurs] = nom;
    printf("Le conducteur %s a bien été ajouté !\n", nom);
    (*NB_conducteurs)++;
}

/**
 * @brief Modifie un ID de conducteur dans la liste des ID existants.
 *
 * @param[in] villes Liste des ID de conducteurs existants.
 * @param[in] NB_villes Pointeur vers le nombre d'ID de conducteurs existants.
 */
void edit_IDc(const char** villes, int* NB_villes) {
    printf("ID du conducteur à modifier : ");
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
            printf("Nouvel ID : ");
            char nom[50];
            scanf("%s", nom);

            villes[*NB_villes] = nom;
            printf("L'ID a bien été modifié en %s !\n", nom);
            (*NB_villes)++;

            break;
        }
    }
    if (!found) {
        printf("L'ID %s n'a pas été trouvé\n", nom);
    }
}

/**
 * @brief Supprime un ID de conducteur de la liste des ID existants.
 *
 * @param[in] villes Liste des ID de conducteurs existants.
 * @param[in,out] NB_villes Pointeur vers le nombre d'ID de conducteurs existants.
 */
void sup_IDc(const char** villes, int* NB_villes) {
    printf("ID du conducteur à supprimer : ");
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
            printf("L'ID %s a été supprimé avec succès !\n", nom);
            break;
        }
    }
    if (!found) {
        printf("L'ID %s n'a pas été trouvé\n", nom);
    }
}


/////// CONDUCTEUR ///////////////////////

/**
 * @brief Crée un nouveau trajet en demandant au conducteur toutes les villes et tous les horaires de départ
 *
 * @param[in] conducteur Nom du conducteur du trajet.
 * @param[in] villes Liste des ID de villes existantes.
 * @param[in] NB_villes Nombre d'ID de villes existantes.
 * @param[in,out] listetrajos Liste des trajets existants.
 * @param[in,out] NB_trajets Pointeur vers le nombre de trajets existants.
 */
void creer_trajet(const char* conducteur, const char** villes, int* NB_villes, Trajet* listetrajos, int* NB_trajets) {
    printf("Vous allez créer un trajet. Lors de la saisie assurez-vous de n'entrer que des noms de villes desservies.\nDe plus, votre trajet ne peut se dérouler que sur une seule journée.\n\n");
    int date_ok = 0;
    int an;
    int mo;
    int jo;
    int he;
    int mi;

    Date* liste_date = malloc(50 * sizeof(Date));
    Troncon* liste_tronc = malloc(50 * sizeof(Troncon));

    // Première ville
    while (date_ok == 0) {
        printf("Entrez la date de votre départ :\n");
        printf("L'année de départ :");
        scanf("%d", &an);

        printf("Le mois de départ (entre 1 et 12) :");
        scanf("%d", &mo);

        printf("Le jour de départ (entre 1 et 31) :");
        scanf("%d", &jo);

        int jours_par_mois[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        date_ok = 1;
        if ((an % 4 == 0 && an % 100 != 0) || an % 400 == 0) {
            jours_par_mois[2] = 29;
        }
        if (an < 2000 || an > 2100) {
            printf("Année inexistante");
            date_ok = 0;
        }
        if (mo < 1 || mo > 12) {
            printf("Mois inexistant");
            date_ok = 0;
        }
        if (jo < 1 || jo > jours_par_mois[mo]) {
            printf("Jour inexistant");
            date_ok = 0;
        }

        if (date_ok == 0) {
            printf("Erreur de saisie dans la date. Veuillez vérifier que la date saisie existe.\n");
        }
    }

    int nb_v = 0; // Nombre de villes
    while (nb_v <= 0) {
        printf("Entrez le nombre de villes par lesquelles vous allez passer (en comptant le départ) : ");
        scanf("%d", &nb_v);
        if (nb_v <= 0) {
            printf("Erreur de saisie");
        }
    }

    int dep_ok = 0; // Vérification de la ville de départ
    char v_dep[50];
    // Entrer la ville de départ
    while (dep_ok == 0) {
        printf("Entrez le nom de la ville de départ : ");
        scanf("%s", v_dep);
        dep_ok = ville_valide(villes, NB_villes, v_dep);
        if (dep_ok == 0) {
            printf("Ville inexistante");
        }
    }
    char v_fin[50];
    for (int i = 0; i < (nb_v - 1); i++) {
        liste_tronc[i] = malloc(sizeof(struct s_troncon));
        int date_ok = 0;

        // Date de départ du tronçon
        while (date_ok == 0) {
            printf("Entrez l'heure à laquelle vous partirez de %s :\n", v_dep);
            printf("L'heure (entre 8 et 20) :");
            scanf("%d", &he);

            printf("Les minutes (entre 0 et 59) : ");
            scanf("%d", &mi);

            date_ok = date_valide(an, mo, jo, he, mi);
            if (date_ok == 0) {
                printf("Erreur de saisie dans la date. Veuillez vérifier que la date saisie existe.\n");
            }
        }

        int fin_ok = 0;

        // Définition de la ville d'arrivée du tronçon
        while (fin_ok == 0) {
            printf("Entrez le nom de la ville suivante : ");
            scanf("%s", v_fin);
            fin_ok = ville_valide(villes, NB_villes, v_fin);
            if (fin_ok == 0) {
                printf("Ville inexistante");
            }
        }

        char* ville_dep = malloc(strlen(v_dep) + 1);
        char* ville_fin = malloc(strlen(v_fin) + 1);

        // Copier la ville de départ et d'arrivée dans la mémoire allouée
        strcpy(ville_dep, v_dep);
        strcpy(ville_fin, v_fin);

        liste_date[i] = allocDate(an, mo, jo, he, mi);

        liste_tronc[i]->ville_depart = ville_dep;
        liste_tronc[i]->ville_fin = ville_fin;
        liste_tronc[i]->date_tronc = liste_date[i];

        strcpy(v_dep, v_fin);
    }

    Trajet trajet = allocTrajet(conducteur, nb_v, liste_tronc);

    listetrajos[*NB_trajets] = trajet;
    printf("Bien reçu !\n\n");
    (*NB_trajets)++;
}

/**
 * @brief Affiche les trajets d'un conducteur spécifique.
 *
 * @param[in] trajets Liste des trajets existants.
 * @param[in] NB_trajets Nombre de trajets existants.
 * @param[in] conducteur Nom du conducteur.
 */
void afficher_trajets(Trajet* trajets, int* NB_trajets, const char* conducteur) {
    for (int i = 0; i < *NB_trajets; i++) {
        if (strcmp(trajets[i]->conducteur, conducteur) == 0) {
            printf("TRAJET DU %d/%d %d :\n\n", trajets[i]->liste_tronc[0]->date_tronc->jour, trajets[i]->liste_tronc[0]->date_tronc->mois, trajets[i]->liste_tronc[0]->date_tronc->annee);
            for (int j = 0; j < trajets[i]->nbVilles - 1; j++) {
                printf("%d - Ville de départ : %s ; Départ à : %d h %d ; Ville d'arrivée : %s\n\n\n", j + 1, trajets[i]->liste_tronc[j]->ville_depart, trajets[i]->liste_tronc[j]->date_tronc->heure, trajets[i]->liste_tronc[j]->date_tronc->minute, trajets[i]->liste_tronc[j]->ville_fin);
            }
        }
    }
}


/////////////////// CLIENT ///////////////////////////////

/**
 * @brief Permet à un client de réserver un trajet en rentrant l'identifiant du trajet, et les tronçons du trajet sur lequels il veut s'inscrire
 *
 * @param[in] trajets Liste des trajets existants.
 * @param[in,out] NB_trajets Nombre de trajets existants.
 * @param[in] villes Liste des villes existantes.
 * @param[in] client Nom du client.
 */
void reserver_trajet(Trajet* trajets, int* NB_trajets, const char** villes, const char* client) {
    printf("Veuillez rentrer l'identifiant du trajet sur lequel vous souhaitez vous inscrire ( Vous pouvez récupérer cet Identifiant en recherchant un trajet ) :\n");
    int id_traj = -1;
    while ((!(0 <= id_traj) || !(id_traj < *NB_trajets))) {
        printf("Entrez l'Identifiant du trajet : ");
        scanf("%d", &id_traj);
        if ((!(0 <= id_traj) || !(id_traj < *NB_trajets))) {
            printf("Identifiant inexistant\n");
            exit(0);
        }
    }
    printf("Rentrez votre ville de départ : ");
    char dep[50];
    scanf("%s", dep);
    printf("Rentrez votre ville d'arrivée : ");
    char arr[50];
    scanf("%s", arr);
    for (int j = 0; j < trajets[id_traj]->nbVilles - 1; j++) {
        if (strcmp(trajets[id_traj]->liste_tronc[j]->ville_depart, dep) == 0) {
            int nb_dep = j;
            int place_libre = 1;
            for (int j = nb_dep; j < trajets[id_traj]->nbVilles - 1; j++) {
                if (!(trajets[id_traj]->liste_tronc[j]->passagersId[1] == trajets[id_traj]->liste_tronc[j]->passagersId[50])) {
                    place_libre = 0;
                    printf("Plus de places disponibles");
                    // Mettre menu_client
                }
                if (strcmp(trajets[id_traj]->liste_tronc[j]->ville_fin, arr) == 0 && place_libre == 1) {
                    int nb_arr = j;
                    for (int k = nb_dep; k <= nb_arr; k++) {
                        if (trajets[id_traj]->liste_tronc[k]->passagersId[0] == trajets[id_traj]->liste_tronc[j]->passagersId[50]) {
                            trajets[id_traj]->liste_tronc[k]->passagersId[0] = client;
                        }
                        else {
                            trajets[id_traj]->liste_tronc[k]->passagersId[1] = client;
                        }
                    }
                    printf("Inscription validée : Votre Trajet : départ de %s à %d h %d\n", trajets[id_traj]->liste_tronc[nb_dep]->ville_depart, trajets[id_traj]->liste_tronc[nb_dep]->date_tronc->heure, trajets[id_traj]->liste_tronc[nb_dep]->date_tronc->minute);
                    // main(); // Mettre menu_client
                }
            }
        }
    }
    printf("Le trajet choisi ne comprend pas les villes désirées");
    // main(); // Mettre menu_client
}



/**
 * @brief Affiche le menu du client et permet de choisir une action.
 *
 * @param[in] admin Administrateur du système.
 * @param[in] villes Liste des villes existantes.
 * @param[in,out] NB_villes Nombre de villes existantes.
 * @param[in] conds Liste des conditions existantes.
 * @param[in,out] NB_conds Nombre de conditions existantes.
 * @param[in] mdpconds Liste des mots de passe des conditions.
 * @param[in] trajets Liste des trajets existants.
 * @param[in,out] NB_trajets Nombre de trajets existants.
 * @param[in] client Nom du client.
 * @param[in] clients Liste des clients existants.
 * @param[in,out] NB_clients Nombre de clients existants.
 * @param[in] MDPclients Liste des mots de passe des clients.
 */
void menu_client(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char* client, const char** clients, int* NB_clients, const char** MDPclients) {
    int choix;
    printf("Vous voulez : \n");
    printf("1- Chercher un trajet\n");
    printf("2- Réserver un trajet\n");
    printf("3- Revenir au menu principal\n\n");
    scanf("%d", &choix);
    if (choix == 1) {
        afficher_tous_trajets(trajets, conds, NB_trajets, NB_conds);
    }
    else if (choix == 2) {
        reserver_trajet(trajets, NB_trajets, villes, client);
    }
    else if (choix == 3) {
        menuprincipal(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, clients, NB_clients, MDPclients);
    }
    else {
        printf("Choix invalide\n");
        menu_client(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, client, clients, NB_clients, MDPclients);
    }
}

/**
 * @brief Permet à un client de se connecter.
 *
 * @param[in] admin Administrateur du système.
 * @param[in] villes Liste des villes existantes.
 * @param[in,out] NB_villes Nombre de villes existantes.
 * @param[in] conds Liste des conditions existantes.
 * @param[in,out] NB_conds Nombre de conditions existantes.
 * @param[in] mdpconds Liste des mots de passe des conditions.
 * @param[in] trajets Liste des trajets existants.
 * @param[in,out] NB_trajets Nombre de trajets existants.
 * @param[in] clients Liste des clients existants.
 * @param[in,out] NB_clients Nombre de clients existants.
 * @param[in] MDPclients Liste des mots de passe des clients.
 */
void login_client(Admin admin, const char** villes, int* NB_villes, const char** conds, int* NB_conds, const char** mdpconds, Trajet* trajets, int* NB_trajets, const char** clients, int* NB_clients, const char** MDPclients) {
    char idclient[20];
    char mdPclient[20];
    printf("Identifiant : ");
    scanf("%s", idclient);
    printf("Mot de passe : ");
    scanf("%s", mdPclient);
    printf("\n");

    for (int i = 0; i < *NB_clients; i++) {

        if (strcmp(clients[i], idclient) == 0) {

            for (int u = 0; u < *NB_clients; u++) {
                if (strcmp(MDPclients[i], mdPclient) == 0) {

                    menu_client(admin, villes, NB_villes, conds, NB_conds, mdpconds, trajets, NB_trajets, idclient, clients, NB_clients, MDPclients);

                }
            }
        }
    }
}

/**
 * @brief Affiche tous les trajets disponibles en fonction des conditions données.
 *
 * @param[in] trajets Liste des trajets existants.
 * @param[in] conds Liste des conditions existantes.
 * @param[in] NB_trajets Nombre de trajets existants.
 * @param[in] NB_conds Nombre de conditions existantes.
 */
void afficher_tous_trajets(Trajet* trajets, const char** conds, int* NB_trajets, int* NB_conds) {
    for (int i = 0; i < *NB_conds; i++) {
        afficher_trajets(trajets, NB_trajets, conds[i]);
    }
}

//----------------MAIN---------------------

int main() {
    /////////////////Déclarations de Variables et Load//////////////////

    json_t* donnee_load = fonction_data_json("/home/olivier/CUPGEs1/tpbash/projetC.json");
    ///////////////////////TAILLES///////////

    int taille_liste_ville_nat = taille_liste_json(donnee_load, "villes");
    int taille_liste_conducteurs_nat = taille_liste_json(donnee_load, "conducteurs");
    int taille_liste_client = taille_liste_json(donnee_load, "clients");


    int taille_liste_trajets = 0; //au lancement du programme aucun trajet dispo au tout debut
    ////////////admin//////x/////

    const char* admin_id = liste_jsonTostr(donnee_load, "id_admin")[0];
    const char* admin_mdp = liste_jsonTostr(donnee_load, "mdp_admin")[0];
    //////////////listes//////
    const char** conds = liste_jsonTostr(donnee_load, "conducteurs");
    const char** mdpconds = liste_jsonTostr(donnee_load, "mdp_conducteurs");
    //////////////////////*/

    const char** villes = liste_jsonTostr(donnee_load, "villes");

    const char** liste_clients = liste_jsonTostr(donnee_load, "clients");
    const char** liste_mdp_clients_main = liste_jsonTostr(donnee_load, "mdp_clients");
    ////////////////TEST//////////*/

    Admin modo = allocAdmin(admin_id, admin_mdp);


    ////////////////////trajets/////////////////

    Trajet* liste_traj = malloc(sizeof(Trajet));

    /////////////////Main//////////////////

    menuprincipal(modo, villes, &taille_liste_ville_nat, conds, &taille_liste_conducteurs_nat, mdpconds, liste_traj, &taille_liste_trajets, liste_clients, &taille_liste_client, liste_mdp_clients_main);

    return 0;
}
