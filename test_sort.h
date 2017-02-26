#ifndef _TEST_SORT_H
#define _TEST_SORT_H

#include "merge_sort.h"
#include "insert_quick_sort.h"
#include "merge_sort_insert_sort.h"
#include "quick_sort.h"
#include "assist.h"

#define LONG_BITS 12
#define MAX_CARD_NUM 999999999

int randomize_cards (int cards[], size_t card_num);
int get_random_number (int max);
int init_random_number (void);
void print_sort_fatal_err_msg(int cur_func);
void print_success_msg (int cur_func, double elapsed);
void print_sort_func_fail_msg (int cur_func);
void print_sort_func_return_err (int cur_func ,int ret);
int get_child_runtime (double *value);
int check_sort_result (int cards[], int orig_cards[], size_t card_num);
void print_cards (int cards[], size_t card_num);
void print_original_cards (int cards[], size_t card_num);
void process_result_of_child (int status, int cards[], size_t card_num, int cur_func);
void sort_cards (int cards[], int orig_cards[], size_t card_num, int(*func)(int[], size_t, int), int cur_func);
void various_sort_cards (int cards[], int orig_cards[], size_t card_num, int(*func[6])(int[], size_t, int));
void print_randomize_cards (int cards[], size_t card_num);
int print_resource_usage(void);

#endif
