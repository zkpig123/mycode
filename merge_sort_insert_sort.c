#include "merge_sort_insert_sort.h"

int _merge_sort_guard_incremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_incremental(cards, left_card_num);
	else _insert_sort_incremental(cards, left_card_num);
	if (right_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_incremental(cards + mid, right_card_num);
	else _insert_sort_incremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num + 1)) == NULL || (right_cards = malloc(right_card_num + 1)) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num);
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num);
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right;
	left = left_cards;
	right = right_cards;
	for (size_t i = 0; i < card_num; i++){
		if (*left < *right) cards[i] = *left++;
		else cards[i] = *right++;
	}
	free(left_cards);
	free(right_cards);
}

int _merge_sort_guard_decremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_decremental(cards, left_card_num);
	else _insert_sort_decremental(cards, left_card_num);
	if (right_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_decremental(cards + mid, right_card_num);
	else _insert_sort_decremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num + 1)) == NULL || (right_cards = malloc(right_card_num + 1)) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num);
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num);
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right;
	left = left_cards;
	right = right_cards;
	for (size_t i = 0; i < card_num; i++){
		if (*left > *right) cards[i] = *left++;
		else cards[i] = *right++;
	}
	free(left_cards);
	free(right_cards);
}

int merge_sort_guard (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num <= 0 || order == 0) return 1;
	else if (card_num == 1) return 0;
	if (order > 0){
		if (card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_incremental(cards, card_num);
		else _insert_sort_incremental(cards, card_num);
	}else{
		if (card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_guard_decremental(cards, card_num);
		else _insert_sort_decremental(cards, card_num);
	}
	return 0;
}

int _merge_sort_non_guard_incremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_incremental(cards, left_card_num);
	else _insert_sort_incremental(cards, left_card_num);
	if (right_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_incremental(cards + mid, right_card_num);
	else _insert_sort_incremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num + 1)) == NULL || (right_cards = malloc(right_card_num + 1)) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num);
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num);
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	for (size_t i = 0; ; ){
		if (left <= left_most){
			if (right <= right_most){
				if (*left < *right) cards[i++] = *left++;
				else cards[i] = *right++;
			}else{
				memcpy(cards + i, left, left_most - left + 1);
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + i, right, right_most - right + 1);
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);
}

int _merge_sort_non_guard_decremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_decremental(cards, left_card_num);
	else _insert_sort_decremental(cards, left_card_num);
	if (right_card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_decremental(cards + mid, right_card_num);
	else _insert_sort_decremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num + 1)) == NULL || (right_cards = malloc(right_card_num + 1)) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num);
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num);
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	for (size_t i = 0; ; ){
		if (left <= left_most){
			if (right <= right_most){
				if (*right < *left) cards[i++] = *left++;
				else cards[i] = *right++;
			}else{
				memcpy(cards + i, left, left_most - left + 1);
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + i, right, right_most - right + 1);
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);
}

int merge_sort_non_guard (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num <= 0 || order == 0) return 1;
	else if (card_num == 1) return 0;
	if (order > 0){
		if (card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_incremental(cards, card_num);
		else _insert_sort_incremental(cards, card_num);
	}else{
		if (card_num >= ITEM_NUM_LESS_THAN_THIS_USE_INSERT_SORT) _merge_sort_non_guard_decremental(cards, card_num);
		else _insert_sort_decremental(cards, card_num);
	}
	return 0;
}

void _insert_sort_incremental (int cards[], size_t card_num)
{
	for (size_t i = 1; i <= card_num - 1; i++){
		int cur = cards[i];
		size_t j;
		for (j = i - 1; j >= 0 && cards[j] > cur; j--){
			cards[j + 1] = cards[j];
		}
		cards[j + 1] = cur;
	}
}

void _insert_sort_decremental (int cards[], size_t card_num)
{
	for (size_t i = 1; i <= card_num - 1; i++){
		int cur = cards[i];
		size_t j;
		for (j = i - 1; j >= 0 && cards[j] < cur; j--){
			cards[j + 1] = cards[j];
		}
		cards[j + 1] = cur;
	}
}

