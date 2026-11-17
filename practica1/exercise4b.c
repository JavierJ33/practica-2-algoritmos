
/**************************************************/
/* Programa: exercise4b      Date:                */
/* Authors: Profesorado                           */
/*                                                */
/* Program that checks QuickSort                  */
/*                                                */
/* Input: Command Line                            */
/* -size: number of elements of each permutation  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char** argv)
{
  int tamano, i, j, ret;
  int* perm = NULL;

  srand(time(NULL));

  if (argc != 3) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -size <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -size : number of elements in the permutation.\n");
    return 0;
  }
  printf("Practice number 2, section 3, 4 and 5\n");
  printf("Done by: Jarque Narro Javier y Gonzalez Hijano Ivan\n");
  printf("Group: 126\n");

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-size") == 0) {
      tamano = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  if (tamano < 1) {
    printf("Error: Invalid size\n");
    return -1;
  }

  for (int alg = 0; alg < 3; alg++) {

    perm = generate_perm(tamano);

    if (perm == NULL) { /* error */
      printf("Error: Out of memory\n");
      exit(-1);
    }

    if (alg == 0) {
      printf("QuickSort_min:\n");
      ret = QuickSort_min(perm, 0, tamano-1);
    }
    else if (alg == 1) {
      printf("QuickSort_mean:\n");
      ret = QuickSort_mean(perm, 0, tamano-1);
    }
    else {
      printf("QuickSort_median:\n");
      ret = QuickSort_median(perm, 0, tamano-1);
    }

    if (ret == ERR) {
      printf("Error: Error in QuickSort\n");
      free(perm);
      exit(-1);
    }

    for(j = 0; j < tamano-1; j++) {
      if (perm[j] > perm[j+1]) {
        printf("Error: Array not sorted\n");
        free(perm);
        exit(-1);
      }
    }

    printf("Array ordenado correctamente\n");

    for(j = 0; j < tamano; j++) {
      printf("%d \t", perm[j]);
    }
    printf("\n");

    printf("OB: %d\n", ret);

    free(perm);
  }

  /* check segments with one or zero elements */
  int unico[] = {42};
  int vacio[] = {10, 20, 30};

  if (QuickSort_min(unico, 0, 0) != 0 ||
      QuickSort_mean(unico, 0, 0) != 0 ||
      QuickSort_median(unico, 0, 0) != 0) {
    printf("Error: Segment with one element\n");
    return -1;
  }

  if (QuickSort_min(vacio, 0, -1) != 0 ||
      QuickSort_mean(vacio, 0, -1) != 0 ||
      QuickSort_median(vacio, 0, -1) != 0) {
    printf("Error: Empty segment\n");
    return -1;
  }

  printf("Casos limite correctos\n");

  return 0;
}
