#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "entreprise_covolturage.h"

#define MAX_VILLES 9
#define MAX_CONDUCTEURS 100
#define MAX_CLIENTS 100

// Fonction principale
int main() {

    typedef struct {
        char nom[50];
    } Ville;

    typedef struct {
        char nom[50];
        char vehicule[20];
        int places_disponibles;
        int trajet[MAX_VILLES];
    } Conducteur;

    typedef struct {
        char nom[50];
        char trajet[20];
        int nb_personnes;
    } Client;

    typedef struct {
        char date[20];
        int ville_depart;
        int ville_arrivee;
        int places_disponibles;
        int clients[MAX_CLIENTS];
    } Trajet;

    Ville villes[MAX_VILLES] = { {"Lille"}, {"Paris"}, {"Strasbourg"}, {"Lyon"}, {"Bordeaux"}, {"Toulouse"}, {"Montpellier"}, {"Marseille"}, {"Nice"} };
    Conducteur conducteurs[MAX_CONDUCTEURS];
    int nb_conducteurs = 0;
    Client clients[MAX_CLIENTS];
    int nb_clients = 0;
    Trajet trajets[MAX_VILLES * MAX_VILLES];
    int nb_trajets = 0;
    char admin_password[20] = "admin";


    // Boucle principale du programme
    int choix_menu = -1;
    while (choix_menu != 9) {

        // Affichage des menus et saisie utilisateur
        choix_menu = afficher_menu();

        // Traitement de la saisie utilisateur
        switch (choix_menu) {
        case 1:
            // Gestion des villes
            gerer_villes();
            break;
        case 2:
            // Exportation des conducteurs au format JSON
            exporter_conducteurs_JSON();
            break;
        case 3:
            // Administration de comptes
            administrer_comptes();
            break;
        case 4:
            // Offre de trajet pour les conducteurs
            offrir_trajet_conducteur();
            break;
        case 5:
            // Recherche de trajets pour les conducteurs
            rechercher_trajets_conducteur();
            break;
        case 6:
            // Administration de comptes conducteurs
            administrer_compte_conducteur();
            break;
        case 7:
            // Recherche de trajets pour les clients
            rechercher_trajets_client();
            break;
        case 8:
            // Réservation/modification de trajets pour les clients
            reserver_modifier_trajet_client();
            break;
        case 9:
            // Quitter le programme
            printf("Au revoir !\n");
            break;
        default:
            // Gestion d'une saisie invalide
            printf("Saisie invalide. Veuillez saisir un choix valide.\n");
            break;
        }

    }

    // Libération de la mémoire allouée
    // ...

    return 0;
}

// Fonctions pour chaque menu
int afficher_menu() {
    // Affichage du menu et saisie utilisateur
    // ...
    printf("Bienvenu !\n");
    printf("Pour parcourir notre application veuillez saisir un nombre de 1 à 9 pour accéder a l'espace\n\n");
    printf("1. Gestions des Villes");
    printf("2. Liste des Conducteurs");
    printf("3. Gérer les Comptes");
    printf("4. Proposer un trajet (espace Conduteur)");
    printf("5. Sélectionner un trajet (espace Conducteur)");
    printf("6. Gérer les Comptes Conduteurs");
    printf("7. Choisir un trajet (espace Client)");
    printf("8. Modifier / Annuler un trajet (espace Client)");
    printf("9. Quitter");
    int choix_utilisateur;
    scanf( "Sélectionnez un paramètre : ", &choix_utilisateur );
    return choix_utilisateur;
}

void gerer_villes() {
    // Ajout, modification ou suppression de villes
    // ...
}

void exporter_conducteurs_JSON() {
    // Exportation des conducteurs au format JSON
    // ...
}

void administrer_comptes() {
    // Changement de mot de passe pour conducteurs ou clients
    // ...
}

void offrir_trajet_conducteur() {
    // Création d'un nouveau trajet pour un conducteur
    // ...
}

void rechercher_trajets_conducteur() {
    // Recherche des trajets pour un conducteur
    // ...
}

void administrer_compte_conducteur() {
    // Changement de mot de passe ou de coordonnées pour un conducteur
    // ...
}

void rechercher_trajets_client() {
    // Recherche de trajets pour un client
    // ...
}

void reserver_modifier_trajet_client() {
    // Réservation ou modification d'un trajet pour un client
    // ...
}

