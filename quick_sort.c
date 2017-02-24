#include "quick_sort.h"
#define K 30

void swap_int (int *n1, int *n2)
{
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;
}

int _quick_sort_from_side_incremental (int cards[], size_t card_num)
{
	time_t cur_time = time(NULL);
	if (cur_time == (time_t)-1) return 1;
	srandom((unsigned int)cur_time);
	size_t base = random() % card_num;
	swap_int(cards, &cards[base - 1]); //swap cards[0] and cards[base-1]
	size_t base_final_pos = 0;
	for (size_t i = 1; i <= card_num - 1; i++){
		if (cards[i] < cards[0]){
			base_final_pos++;
			swap_int(&cards[base_final_pos], &cards[i]);
		}
	}
	swap_int(&cards[0], &cards[base_final_pos]);
	size_t left_card_num, right_card_num;
	left_card_num = base_final_pos;
	right_card_num = card_num - left_card_num - 1;
	if (left_card_num > K){
		if (_quick_sort_from_side_incremental(cards, left_card_num)) return 2;
	}else{
		if (left_card_num > 1) _insert_sort_incremental(cards, left_card_num);
	}
	if (right_card_num > K){
		if (_quick_sort_from_side_incremental(cards + base_final_pos + 1, right_card_num)) return 2;
	}else{
		if (right_card_num > 1) _insert_sort_incremental(cards + base_final_pos + 1, right_card_num);
	}
	return 0;
}

int _quick_sort_from_side_decremental (int cards[], size_t card_num)
{
	time_t cur_time = time(NULL);
	if (cur_time == (time_t)-1) return 1;
	srandom((unsigned int)cur_time);
	size_t base = random() % card_num;
	swap_int(cards, &cards[base - 1]); //swap cards[0] and cards[base-1]
	int base_final_pos = 0;
	for (size_t i = 1; i <= card_num - 1; i++){
		if (cards[i] > cards[0]){
			base_final_pos++;
			swap_int(&cards[base_final_pos], &cards[i]);
		}
	}
	swap_int(&cards[0], &cards[base_final_pos]);
	size_t left_card_num, right_card_num;
	left_card_num = base_final_pos;
	right_card_num = card_num - left_card_num - 1;
	if (left_card_num > K){
		if (_quick_sort_from_side_decremental(cards, left_card_num)) return 2;
	}else{
		if (left_card_num > 1) _insert_sort_decremental(cards, left_card_num);
	}
	if (right_card_num > K){
		if (_quick_sort_from_side_decremental(cards + base_final_pos + 1, right_card_num)) return 2;
	}else{
		if (right_card_num > 1) _insert_sort_decremental(cards + base_final_pos + 1, right_card_num);
	}
	return 0;
}

int quick_sort_from_side (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num == 0 || order == 0) return 1;
	if (card_num == 1) return 0;
	if (order > 0){
		if (card_num == 2){
			if (cards[0] > cards[1]) swap_int(&cards[0], &cards[1]);
		}else if (card_num <= K) _insert_sort_incremental(cards, card_num);
		else{
			if (_quick_sort_from_side_incremental(cards, card_num)) return 2;
		}
	}else{
		if (card_num == 2){
			if (cards[0] < cards[1]) swap_int(&cards[0], &cards[1]);
		}else if (card_num <= K) _insert_sort_decremental(cards, card_num);
		else{
			if (_quick_sort_from_side_decremental(cards, card_num)) return 3;
		}
	}
	return 0;
}
