#ifndef _QUICK_SORT_H
#define _QUICK_SORT_H

#include "insert_sort.h"
#include "assist.h"

#define K 30

int init_random (void);
void swap_int (int *n1, int *n2);
int _quick_sort_from_side_incremental (int cards[], size_t card_num);
int _quick_sort_from_side_decremental (int cards[], size_t card_num);
int quick_sort_from_side (int cards[], size_t card_num, int order);

#endif
