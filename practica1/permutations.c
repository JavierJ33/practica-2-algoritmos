/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include <stdlib.h>
#include <limits.h>
#include "permutations.h"


/***************************************************/
/* Function: random_num Date: 30/09/2026           */
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Routine that generates a uniform pseudo-random  */
/* integer in the closed interval [inf, sup].      */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit of the interval (>= 0)     */
/* int sup: upper limit of the interval (>= inf)   */
/* Output:                                         */
/* int: generated random number, or ERR in case of */
/*      invalid arguments or arithmetic overflow.  */
/***************************************************/

int random_num(int inf, int sup)
{

  if(inf>sup || inf < 0 || sup < 0){
    return ERR;
  }
  
  if (sup - inf > RAND_MAX || sup - inf == INT_MAX){
    return ERR;
  }
  int diferencia = sup - inf + 1;
  return inf + rand() % diferencia;
}

/***************************************************/
/* Function: swap_p     Date: 30/09/2026           */
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Helper function that swaps the integer values   */
/* stored at two memory addresses.                 */
/*                                                 */
/* Input:                                          */
/* int *a: non-NULL pointer to the first element   */
/* int *b: non-NULL pointer to the second element  */
/* Output: none                                    */
/***************************************************/

void swap_p(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
  return;
}

/***************************************************/
/* Function: free_permutations Date: 09/10/2026    */
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Safely frees a dynamic 2D array of permutations */
/* up to a given number of allocated rows.         */
/*                                                 */
/* Input:                                          */
/* int **permutation: array of permutation pointers*/
/* int n_permutations: number of allocated rows    */
/* Output: none                                    */
/***************************************************/

int *generate_perm(int N)
{
  if (N <= 0)
  {
    return NULL;
  }

  int *perm = (int *)malloc(sizeof(perm[0]) * N);
  if (perm==NULL)
    return NULL;

  for (int i = 0; i < N; i++)
  {
    perm[i] = i + 1;
  }

  for (int i = 0; i < N; i++)
  {
    int rnd = random_num(i, N-1);
    if(rnd==ERR){
      free(perm);
      return NULL;
    }
    swap_p(&perm[i], &perm[rnd]);
    // int aux = perm[i];
    // perm[i] = perm[rnd];
    // perm[rnd] = aux;
  }
  return perm;
}

/***************************************************/
/* Function: generate_permutations Date: 09/10/2026*/
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Generates an array of n_perms independent       */
/* random permutations of size N each.             */
/*                                                 */
/* Input:                                          */
/* int n_perms: number of permutations to generate */
/* int N: size of each permutation                 */
/* Output:                                         */
/* int**: array of pointers to the permutations,   */
/*        or NULL in case of error.                */
/***************************************************/
int **generate_permutations(int n_perms, int N)
{
  if (N <= 0 || n_perms <= 0)
    return NULL;

  int **result = (int **)malloc(sizeof(result[0]) * n_perms);
  if (result==NULL)
  {
    return NULL;
  }

  for (int i = 0; i < n_perms; ++i)
  {
    result[i] = generate_perm(N);
    if (result[i]==NULL)
    {
      free_permutations(result, i);
      return NULL;
    }
  }

  return result;
}


/***************************************************/
/* Function: free_permutations   Date: 30/09/2026  */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Function that frees the memory of permutations  */
/*                                                 */
/* Input:                                          */
/* int **permutation: array of pointers to integer */
/* int n_permutations: number of permutations      */
/* Output:                                         */
/* void: frees the permutations and their array    */
/***************************************************/
void free_permutations(int **permutation, int n_permutations){
  if (permutation == NULL){
    return;
  }
  for (int i = 0; i < n_permutations; i++)
      {
        free(permutation[i]);
      }
      free(permutation);
      return;
}