#ifndef COVOITURAGE_H
#define COVOITURAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VILLES 9
#define MAX_TRAJETS 100
#define MAX_CONDUCTEURS 50
#define MAX_CLIENTS 100

typedef struct {
    char nom[20];
} Ville;

typedef struct {
    char ville_depart[20];
    char ville_arrivee[20];
    char date[11];
    int conducteur_id;
    int clients_ids[2];
} Trajet;

typedef struct {
    char nom[20];
    char prenom[20];
    char mot_de_passe[20];
    int nb_trajets;
    int trajets_ids[MAX_TRAJETS];
} Conducteur;

typedef struct {
    char nom[20];
    char prenom[20];
    char mot_de_passe[20];
    int nb_trajets;
    int trajets_ids[MAX_TRAJETS];
} Client;

// Fonctions pour la gestion des villes
void ajouter_ville(Ville* villes, int* nb_villes);
void modifier_ville(Ville* villes, int nb_villes);
void supprimer_ville(Ville* villes, int* nb_villes);

// Fonctions pour l'administration
void changer_mot_de_passe(Conducteur* conducteurs, int nb_conducteurs, Client* clients, int nb_clients);
void exporter_conducteurs(Conducteur* conducteurs, int nb_conducteurs);

// Fonctions pour les conducteurs
void creer_trajet(Conducteur* conducteur, Trajet* trajets, int* nb_trajets, Ville* villes, int nb_villes);
void afficher_trajets(Conducteur conducteur, Trajet* trajets, int nb_trajets, Ville* villes, int nb_villes);
void changer_mot_de_passe_conducteur(Conducteur* conducteur);
void changer_coordonnees_conducteur(Conducteur* conducteur);

// Fonctions pour les clients
void chercher_trajet(Trajet* trajets, int nb_trajets, Ville* villes, int nb_villes);
void reserver_trajet(Trajet* trajets, int nb_trajets, Client* client, Conducteur* conducteurs, int nb_conducteurs, Ville* villes, int nb_villes);
void modifier_trajet(Client* client, Trajet* trajets, int nb_trajets, Ville* villes, int nb_villes);
void changer_mot_de_passe_client(Client* client);
void changer_coordonnees_client(Client* client);

#endif
