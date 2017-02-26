#ifndef _INSERT_QUICK_SORT_H
#define _INSERT_QUICK_SORT_H

#include <stdlib.h>
#include <string.h>
#include "assist.h"

int *_binary_search_incremental(int cards[], size_t card_num, int target);
int *_binary_search_decremental(int cards[], size_t card_num, int target);
int _insert_quick_sort_incremental (int cards[], size_t card_num);
int _insert_quick_sort_decremental (int cards[], size_t card_num);
int insert_quick_sort (int cards[], size_t card_num, int sort_order);

#endif
