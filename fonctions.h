#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// typedef struct Struct_Date{

//   int jour;
//   int mois;
//   int annee;

// }Date;

typedef struct Struct_Personne{
    int id;
    char * nom;
    char * prenom;
    char * datenaissance;   // mettre type Date après
    char * nationalite;

}Personne;


typedef struct Struct_Film{
  int id;
  char * titre;
  int anneeDeSortie;
  Personne * realisateur;
  Personne ** artiste;
  int duree;
  enum {Action, Horreur, Comedie, Documentaire, Policier, Drame, Animation, ScienceFiction} genre; 

}Film;

// const char* getfield(char** line, int num);

char** getFields(char* line, int *nbColumns);

char** readCSV(char fichier[], int *nbLines);

void afficherFilms(char **linesF, int nbLinesF, char **linesA, int nbLinesA);

void parsingCSV();