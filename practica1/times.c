/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"

/***************************************************/
/* Function: average_sorting_time Date: 14/10/2026 */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Function that measures average sorting time and */
/* operation counts for randomly generated inputs  */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: sorting function to measure  */
/* int n_perms: number of permutations to sort     */
/* int N: number of elements per permutation       */
/* PTIME_AA ptime: structure to store the results  */
/* Output:                                         */
/* short: OK on success or ERR if an error occurs; */
/* stores the measurements in ptime on success     */
/***************************************************/
short average_sorting_time(pfunc_sort metodo,
                           int n_perms,
                           int N,
                           PTIME_AA ptime)
{

  if (metodo == NULL || ptime == NULL || n_perms <= 0 || N <= 0)
  {
    return ERR;
  }

  long long OB_counter = 0;
  int OB_min = INT_MAX;
  int OB_max = 0;
  int aux;
  int **perms = generate_permutations(n_perms, N);

  if (perms == NULL)
  {
    return ERR;
  }

  clock_t ttime_ini = clock();
  if (ttime_ini == (clock_t)-1)
  {
    free_permutations(perms, n_perms);
    return ERR;
  }

  for (int i = 0; i < n_perms; i++)
  {
    aux = metodo(perms[i], 0, N - 1);
    if (aux == ERR)
    {
      free_permutations(perms, n_perms);
      return ERR;
    }
    if (aux > OB_max)
    {
      OB_max = aux;
    }
    if (aux < OB_min)
    {
      OB_min = aux;
    }
    OB_counter += aux;
  }
  clock_t ttime_fin = clock();
  if (ttime_fin == (clock_t)-1)
  {
    free_permutations(perms, n_perms);
    return ERR;
  }

  for(int i=0 ; i < n_perms; i++){
    for(int j=0; j < N-1; j++){
      if(perms[i][j] > perms[i][j+1]){
        free_permutations(perms, n_perms);
        return ERR;
      }
    }
  }

  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = (double)(ttime_fin - ttime_ini) / CLOCKS_PER_SEC / n_perms;
  ptime->average_ob = (double)OB_counter / n_perms;
  ptime->max_ob = OB_max;
  ptime->min_ob = OB_min;

  free_permutations(perms, n_perms);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:09/10/2026*/
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Generates sorting statistics across an interval */
/* of sizes [num_min, num_max] with step incr and  */
/* saves the resulting table to a file.            */
/*                                                 */
/* Input:                                          */
/* pfunc_sort method: pointer to sorting function  */
/* char* file: path to destination file            */
/* int num_min: minimum table size (>= 1)          */
/* int num_max: maximum table size (>= num_min)    */
/* int incr: increment step between sizes (> 0)    */
/* int n_perms: number of permutations per size    */
/* Output:                                         */
/* short: OK on success, ERR on error.             */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
                             int num_min, int num_max,
                             int incr, int n_perms)
{
  if(method == NULL || file == NULL || num_min < 1 || num_min > num_max || incr <= 0 || n_perms <= 0){
    return ERR;
  }
  // buscamos num de elementos tal que num_min + Kmax * incr <= num_max
  int kmax = (num_max - num_min) / incr + 1;
  PTIME_AA ptime = (PTIME_AA)malloc(sizeof(TIME_AA) * kmax);
  if (ptime == NULL)
  {
    return ERR;
  }
  int k = 0;
  while (1)
  {
    int N = num_min + k * incr;
    if (N > num_max)
      break;
    short result = average_sorting_time(method, n_perms, N, &ptime[k]);
    if (result == ERR){
      free(ptime);
      return ERR;
    }
    k++;
  }
  int ret_fun = save_time_table(file, ptime, k);
  free(ptime);
  return ret_fun;
}

/***************************************************/
/* Function: save_time_table Date: 14/10/2026      */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Function that saves sorting time data to a file */
/*                                                 */
/* Input:                                          */
/* char *file: path of the output file             */
/* PTIME_AA ptime: array of time measurements      */
/* int n_times: number of measurements to write    */
/* Output:                                         */
/* short: OK on success or ERR if an error occurs; */
/* writes the measurements to the specified file  */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
  if (file == NULL || ptime == NULL || n_times <= 0)
  {
    return ERR;
  }

  FILE *archivo = fopen(file, "w");

  if (archivo == NULL)
  {
    return ERR;
  }
  int counter=0;
  for (int i = 0; i < n_times; i++)
  {
    counter = fprintf(archivo, "%d %d %.9f %.6f %d %d\n", ptime[i].N, ptime[i].n_elems, ptime[i].time, ptime[i].average_ob, ptime[i].min_ob, ptime[i].max_ob);
    if(counter<0){
      fclose(archivo);
      return ERR;
    }
  }

  fclose(archivo);
  return OK;
}
