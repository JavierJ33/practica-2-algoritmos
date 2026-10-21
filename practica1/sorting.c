/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdlib.h>
#include "sorting.h"

/***************************************************/
/* Function: InsertSort Date: 06/10/2026           */
/* Authors: Javier Jarque Narro,                   */
/*          Iván González Hijano                   */
/*                                                 */
/* Sorts an array subsegment [ip, iu] in ascending */
/* order using Insertion Sort and counts the       */
/* number of evaluations of its Basic Operation.   */
/*                                                 */
/* Input:                                          */
/* int *array: non-NULL pointer to the integer tab */
/* int ip: starting index (0 <= ip <= iu)          */
/* int iu: ending index                            */
/* Output:                                         */
/* int: total number of OB evaluations, or ERR.    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  int OB = 0;
  if (array==NULL || ip < 0 || iu < ip)
    return ERR;
  for (int i = ip + 1; i < iu + 1; i++)
  {
    int aux = array[i];
    int j = i - 1;
    while (j >= ip)
    {
      OB++;
      if (array[j] <= aux)
      {
        break;
      }
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = aux;
  }
  return OB;
}

/***************************************************/
/* Function: swap_s          Date: 06/10/2026      */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Helper function that swaps the values of two    */
/* elements                                        */
/*                                                 */
/* Input:                                          */
/* int *a: pointer to the first element            */
/* int *b: pointer to the second element           */
/* Output:                                         */
/* void: swaps the values pointed to by a and b    */
/***************************************************/

void swap_s(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
  return;
}

/***************************************************/
/* Function: BubbleSort    Date: 06/10/2026        */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Function that sorts an array using bubble sort  */
/*                                                 */
/* Input:                                          */
/* int *array: array of integers to sort           */
/* int ip: first index of the range to sort        */
/* int iu: last index of the range to sort         */
/* Output:                                         */
/* int: number of element comparisons, or ERR if   */
/* the input is invalid                            */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
  if (array == NULL || ip < 0 || iu < ip)
  {
    return ERR;
  }

  int OB = 0;
  for (int i = iu; i > ip; i--)
  {
    for (int j = ip; j < i; j++)
    {
      OB++;
      if (array[j] > array[j + 1])
      {
        swap_s(&array[j], &array[j + 1]);
      }
    }
  }
  return OB;
}


int merge(int* array, int ip, int iu, int im);

int MergeSort(int* array, int ip, int iu)
{
  int im;

  if (!array || ip > iu) return ERR;
  if (ip == iu) return 1;

  im = (ip + iu) / 2;
  MergeSort_rec(array, ip, im);
  MergeSort_rec(array, im+1, iu);
  return merge (array, ip, im, iu);
}

