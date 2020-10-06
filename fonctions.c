#include "fonctions.h"

void printPersonne(Personne *p) {
  printf("\nPersonne :\n");
  printf("Id : %d\n", p->id);
  printf("Prénom : %s\n", p->prenom);
  printf("Nom : %s\n", p->nom);
  printf("Date : %s\n", p->datenaissance);
  printf("Nationalite : %s\n", p->nationalite);

}

void printFilm(Film *f, Personne *realisateur) {
  printf("\nFilm :\n");
  printf("Id : %d\n", f->id);
  printf("Titre : %s\n", f->titre);
  printf("Année de sortie : %d\n", f->anneeDeSortie);
  printf("Réalisateur : %s %s\n", f->realisateur->prenom, f->realisateur->nom);
  printf("Durée : %d\n", f->duree);

}

// Retourne un tableau de champs grâce à un id
char** getFieldsFromId(char ** lines, char *id, int nbLinesA) {
	char * delim = ";";
  char **fields = (char**) malloc(sizeof(char)*1);
  char ** fieldsFromLine = (char**) malloc(sizeof(char)*1);
  
  for (int line = 1; line < nbLinesA; line++) {
    int nbColumns = 0;
    fieldsFromLine = getFields(lines[line], &nbColumns);
    if (atoi(fieldsFromLine[0]) == atoi(id)) {
      return fieldsFromLine;

    } else {
      free(fieldsFromLine);
    }
  }
  return NULL;
}

// Retourne un tableau de champs
char** getFields(char *line, int *nbColumns) {
	char * delim = ";";

	char *ptr = strtok(line, delim);

  char **fields = (char**) malloc(sizeof(char)*1);
  int columns = 0;

	while(ptr != NULL) {
    fields[columns] = ptr;
		ptr = strtok(NULL, delim);
    columns++;

	}

  *nbColumns = columns;
  return fields;
}

// Retourne un tableau de lignes
char** readCSV(char fichier[], int *nbLines){
  FILE* stream = fopen(fichier, "r");
  char line[1024];
  char **lines = (char**) malloc(sizeof(char *) * 1);
  int cpt = 0;

  while (fgets(line, 1024, stream)) {
    if (cpt) lines = (char**)realloc(lines, sizeof(char *) * (cpt + 1));
    lines[cpt] = strdup(line);
      
    cpt++;
      
  }
  *nbLines = cpt;
  return lines;

}

void parsingCSV(char **linesF, int nbLinesF, char **linesA, int nbLinesA) {
  
  for (int line = 1; line < nbLinesF; line++) {
    int nbColumns = 0;
    
    char ** fieldsFilm = getFields(linesF[line], &nbColumns);
    char ** fieldsRealisateurFromFilm = getFieldsFromId(linesA, fieldsFilm[3], nbLinesA);
    
    printf("TEST DATE %s\n", fieldsRealisateurFromFilm[3]);
    
    // Creation du realisateur
    Personne *realisateur = (Personne*) malloc(sizeof(Personne));
    printf("TEST DATE %s\n", fieldsRealisateurFromFilm[3]);
    realisateur->id = atoi(fieldsRealisateurFromFilm[0]);
    realisateur->prenom = fieldsRealisateurFromFilm[1];
    realisateur->nom = fieldsRealisateurFromFilm[2];
    printf("TEST DATE %s\n", fieldsRealisateurFromFilm[3]);
    // printf("AAAA : %s", fieldsRealisateurFromFilm[3]);
    realisateur->datenaissance = fieldsRealisateurFromFilm[3];
    realisateur->nationalite = fieldsRealisateurFromFilm[4];
    
    printPersonne(realisateur);
  

    // Faire la déclaration de Film après avoir crée le réalisateur
    Film *film = (Film*) malloc(sizeof(Film));  

    film->id = atoi(fieldsFilm[0]);
    film->titre = (char*) malloc(sizeof(char));
    film->titre = fieldsFilm[1];
    film->anneeDeSortie = atoi(fieldsFilm[2]);
    film->realisateur = (Personne*) malloc(sizeof(Personne));
    film->realisateur = realisateur;
    film->artiste = NULL; // TODO
    film->duree = atoi(fieldsFilm[5]);
    film->genre = Action; // TODO

    printFilm(film, realisateur);
    

    // film->genre = &fieldsFilm[6];

    // printf("le test qui tue : %s\n", ((Personne*) fieldsFilm[3])->prenom);
    // printf("Fiche film n°%d : %s - %d\nRéalisateur : \nActeurs principaux : x, y, z\nDurée : %d\nGenre : \n\n", film->id, film->titre, film->anneeDeSortie, film->duree);
    // for (int column = 1; colum+n < nbColumns; column++) {
    //   printf("%s\n", fieldsFilm[column]);

    // }
    free(realisateur);
    free(film);
    free(fieldsFilm);
    free(fieldsRealisateurFromFilm);
    

  }
}