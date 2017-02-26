#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <stdlib.h>

void _insert_sort_incremental (int cards[], size_t card_num);
void _insert_sort_decremental (int cards[], size_t card_num);
int insert_sort (int cards[], size_t card_num, int sort_order);
void _insert_sort_incremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num);
void _insert_sort_decremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num);
int insert_sort_get_reverse_num (int cards[], size_t card_num, int sort_order, size_t *reverse_num);

#endif
