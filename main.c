#include "fonctions.h"

int main()
{
  int nbLinesA = 0;
  char **linesA = readCSV("artistes.csv", &nbLinesA);

  int nbLinesF = 0;
  char **linesF = readCSV("films.csv", &nbLinesF);
  parsingCSV(linesF, nbLinesF, linesA, nbLinesA);

}