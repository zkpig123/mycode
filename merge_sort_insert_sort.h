#ifndef _MERGE_SORT_INSERT_SORT_H
#define _MERGE_SORT_INSERT_SORT_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT 30
//30 because logn(3n) >= n(n-1)/2

int _merge_sort_guard_incremental (int cards[], size_t card_num);
int _merge_sort_guard_decremental (int cards[], size_t card_num);
int merge_sort_guard (int cards[], size_t card_num, int order);
int _merge_sort_non_guard_incremental (int cards[], size_t card_num);
int _merge_sort_non_guard_decremental (int cards[], size_t card_num);
int merge_sort_non_guard (int cards[], size_t card_num, int order);
void _insert_sort_incremental (int cards[], size_t card_num);
void _insert_sort_decremental (int cards[], size_t card_num);

#endif
