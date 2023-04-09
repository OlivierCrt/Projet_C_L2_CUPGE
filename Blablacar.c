#include <stdio.h>
#include <stdlib.h>
#include "Blablacar.h"

struct s_date {
  int annee;
  int mois;
  int jour;
  int heure;
  int minute;
};

struct s_listeville{
  char* listeville[9];
};

struct s_troncon{
  char* ville_depart;
  char* ville_arrive;
};

struct s_trajet{
  Troncon liste_escales[];
  Date date_trajet;
  int nb_escales;
  Conducteur conducteur_du_trajet;
  Client liste_clients[2];
};
struct s_conducteur{
  char* nom ;
  char*prenom;
  int mot_de_passe;
  
};
struct s_client{
  char* nom ;
  char*prenom;
  int mot_de_passe;
};
  





