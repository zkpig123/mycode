#include <stdlib.h>
#include <string.h>
#include <limits.h>

int _merge_sort_incremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	_merge_sort_incremental(cards, left_card_num);
	_merge_sort_incremental(cards + mid, right_card_num);

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

int _merge_sort_decremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	_merge_sort_incremental(cards, left_card_num);
	_merge_sort_incremental(cards + mid, right_card_num);

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

int merge_sort (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num <= 0 || order == 0) return 1;
	else if (card_num == 1) return 0;
	if (order > 0) _merge_sort_incremental(cards, card_num);
	else _merge_sort_decremental(cards, card_num);
	return 0;
}
