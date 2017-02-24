#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>


int _merge_sort_guard_incremental (int cards[], size_t card_num);
int _merge_sort_guard_decremental (int cards[], size_t card_num);
int merge_sort_guard (int cards[], size_t card_num, int order);
int _merge_sort_non_guard_incremental (int cards[], size_t card_num);
int _merge_sort_non_guard_decremental (int cards[], size_t card_num);
int merge_sort_non_guard (int cards[], size_t card_num, int order);

#endif
