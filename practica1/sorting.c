
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
#include <stdio.h>
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
  if (array == NULL || ip < 0 || iu < ip)
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
 
/***************************************************/
/* Function: merge         Date: 21/10/2026        */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Merges the two sorted halves [ip, im] and       */
/* [im+1, iu] of array into one sorted segment.    */
/* Elements outside [ip, iu] are not modified.     */
/*                                                 */
/* Input:                                          */
/* int *array: array of integers                   */
/* int ip: first index of the segment              */
/* int iu: last index of the segment               */
/* int im: last index of the left half             */
/* Output:                                         */
/* int: number of key comparisons (OB), or ERR if  */
/* the input is invalid or memory allocation fails */
/***************************************************/
int merge(int *array, int ip, int iu, int im)
{
  if (array == NULL || ip < 0 || iu < ip || im < ip || im >= iu)
  {
    return ERR;
  }
 
  n = iu - ip + 1;
  aux = (int *)malloc(n * sizeof(int));
  if (aux == NULL)
  {
    fprintf(stderr, "Error reservando memoria en el merge\n")
    return ERR;
  }
 
  /* Copy the segment to the auxiliary table */
  for (k = 0; k < n; k++)
  {
    aux[k] = array[ip + k];
  }
 
  mid = im - ip; /* last index of the left half inside aux */
  i = 0;
  j = mid + 1;
  k = ip;
 
  while (i <= mid && j < n)
  {
    OB++;
    if (aux[i] <= aux[j])
    {
      array[k++] = aux[i++];
    }
    else
    {
      array[k++] = aux[j++];
    }
  }
  /* Only one of these two loops runs (no comparisons) */
  while (i <= mid)
  {
    array[k++] = aux[i++];
  }
  while (j < n)
  {
    array[k++] = aux[j++];
  }
 
  free(aux);
  return OB;
}
 
/***************************************************/
/* Function: MergeSort     Date: 21/10/2026        */
/* Authors: Gonzalez Hijano, Ivan                  */
/*                                                 */
/* Sorts array[ip..iu] in ascending order using    */
/* MergeSort.                                      */
/*                                                 */
/* Input:                                          */
/* int *array: array of integers                   */
/* int ip: first index of the segment              */
/* int iu: last index of the segment               */
/* Output:                                         */
/* int: number of key comparisons (recursive calls */
/* and merges included), or ERR on error           */
/***************************************************/
int MergeSort(int *array, int ip, int iu)
{
  int im, left, right, mrg;
 
  if (array == NULL || ip < 0 || ip > iu)
    return ERR;
  if (ip == iu)
    return 0;
 
  im = ip + (iu - ip) / 2;
 
  left = MergeSort(array, ip, im);
  if (left == ERR)
    return ERR;
 
  right = MergeSort(array, im + 1, iu);
  if (right == ERR)
    return ERR;
 
  mrg = merge(array, ip, iu, im);
  if (mrg == ERR)
    return ERR;
 
  return left + right + mrg;
}
 
/***************************************************/
/* Function: partition                             */
/*                                                 */
/* Partitions array[ip..iu] around the pivot       */
/* chosen by the function pivot. On exit, *pos is  */
/* the final index of the pivot: smaller keys are  */
/* to its left, the rest to its right.             */
/*                                                 */
/* Input:                                          */
/* int *array: array of integers                   */
/* int ip, iu: first and last index of the segment */
/* int *pos: output, final index of the pivot      */
/* pfunc_pivot pivot: pivot selection function     */
/* Output:                                         */
/* int: key comparisons made by the pivot selector */
/* plus those made while partitioning, or ERR      */
/***************************************************/
int partition(int *array, int ip, int iu, int *pos, pfunc_pivot pivot)
{
  int OB, sel, k, m;
 
  if (array == NULL || ip < 0 || iu < ip || pos == NULL || pivot == NULL)
    return ERR;
 
  sel = pivot(array, ip, iu, &m);
  if (sel == ERR || m < ip || m > iu)
    return ERR;
  OB = sel; /* comparisons of the selector, counted once */
 
  k = array[m];
  swap_s(&array[ip], &array[m]);
  m = ip;
 
  for (int i = ip + 1; i <= iu; i++)
  {
    OB++;
    if (array[i] < k)
    {
      m++;
      swap_s(&array[i], &array[m]);
    }
  }
  swap_s(&array[ip], &array[m]);
 
  *pos = m;
  return OB;
}
 
/***************************************************/
/* Function: pivot_min                             */
/* Pivot = first element of the segment. No key    */
/* comparisons are made.                           */
/* Output: 0, or ERR on invalid input              */
/***************************************************/
int pivot_min(int *array, int ip, int iu, int *pos)
{
  if (array == NULL || ip < 0 || iu < ip || pos == NULL)
    return ERR;
  *pos = ip;
  return 0;
}
 
/***************************************************/
/* Function: pivot_mean                            */
/* Pivot = central index of the segment, computed  */
/* without overflow. No key comparisons are made.  */
/* Output: 0, or ERR on invalid input              */
/***************************************************/
int pivot_mean(int *array, int ip, int iu, int *pos)
{
  if (array == NULL || ip < 0 || iu < ip || pos == NULL)
    return ERR;
  *pos = ip + (iu - ip) / 2;
  return 0;
}
 
/***************************************************/
/* Function: pivot_median                          */
/* Pivot = index of the median of the values at    */
/* ip, ip+(iu-ip)/2 and iu.                        */
/* Output: key comparisons made (2 or 3), or ERR   */
/***************************************************/
int pivot_median(int *array, int ip, int iu, int *pos)
{
  int a, b, c, OB = 0;
 
  if (array == NULL || ip < 0 || iu < ip || pos == NULL)
    return ERR;
  }
  if(iu<=ip){
    return 0;
  }
  int pos;
  
  int ob_partition = partition(array, ip, iu, &pos, pivot_mean);
  if(ob_partition == ERR)
  {
    OB++;
    if (array[b] < array[c])
    {
      *pos = b;
    }
    else
    {
      OB++;
      *pos = (array[a] < array[c]) ? c : a;
    }
  }
  else
  {
    OB++;
    if (array[a] < array[c])
    {
      *pos = a;
    }
    else
    {
      OB++;
      *pos = (array[b] < array[c]) ? c : b;
    }
  }
  return OB;
}
 
/***************************************************/
/* Function: quicksort_rec (static helper)         */
/* Generic QuickSort parametrised by the pivot     */
/* selection function.                             */
/* Output: total key comparisons, or ERR           */
/***************************************************/
static int quicksort_rec(int *array, int ip, int iu, pfunc_pivot pivot)
{
  int pos, OB, left = 0, right = 0;
 
  if (array == NULL || ip < 0 || ip > iu)
    return ERR;
  if (ip == iu)
    return 0;
 
  OB = partition(array, ip, iu, &pos, pivot);
  if (OB == ERR)
    return ERR;
 
  if (ip < pos - 1)
  {
    left = quicksort_rec(array, ip, pos - 1, pivot);
    if (left == ERR)
      return ERR;
  }
  if (pos + 1 < iu)
  {
    right = quicksort_rec(array, pos + 1, iu, pivot);
    if (right == ERR)
      return ERR;
  }

 return ob_partition + QuickSort_left + QuickSort_right;

}
 
int QuickSort_min(int *array, int ip, int iu)
{
  return quicksort_rec(array, ip, iu, pivot_min);
}
 
int QuickSort_mean(int *array, int ip, int iu)
{
  return quicksort_rec(array, ip, iu, pivot_mean);
}
 
int QuickSort_median(int *array, int ip, int iu)
{
  return quicksort_rec(array, ip, iu, pivot_median);
}
