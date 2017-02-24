#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <stdlib.h>

void _insert_sort_incremental (int cards[], size_t card_num);
void _insert_sort_decremental (int cards[], size_t card_num);
int insert_sort (int cards[], size_t card_num, int sort_order);

#endif
