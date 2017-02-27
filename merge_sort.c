#include "merge_sort.h"


int merge_sort_non_guard_get_reverse_num (int cards[], size_t card_num, int order, size_t *reverse_num)
{
	if (cards == NULL || card_num <= 0 || order == 0 || reverse_num == NULL) return 1;
	*reverse_num = 0;
	if (card_num == 1) return 0;
	if (order > 0) _merge_sort_non_guard_incremental_get_reverse_num(cards, card_num, reverse_num);
	else _merge_sort_non_guard_decremental_get_reverse_num(cards, card_num, reverse_num);
	return 0;
}

int _merge_sort_non_guard_incremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num)
{
	*reverse_num = 0;
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	size_t left_reverse_num, right_reverse_num;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	left_reverse_num = right_reverse_num = 0;
	if (left_card_num > 1) _merge_sort_non_guard_incremental_get_reverse_num(cards, left_card_num, &left_reverse_num);
	if (right_card_num > 1) _merge_sort_non_guard_incremental_get_reverse_num(cards + mid, right_card_num, &right_reverse_num);
	*reverse_num += left_reverse_num + right_reverse_num;

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num * sizeof(int))) == NULL || (right_cards = malloc(right_card_num * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	long int cur;
	for (cur = 0; ; cur++){
		if (left <= left_most){
			if (right <= right_most){
				if (*left < *right){
					cards[cur] = *left++;
					if (cur >= left_card_num) *reverse_num += cur /*+ 1*/ - left_card_num;
				}
				else{
					cards[cur] = *right++;
					if (cur < left_card_num) *reverse_num += left_card_num - cur;
				}
			}else{
				memcpy(cards + cur, left, (left_most - left + 1) * sizeof(int));
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + cur, right, (right_most - right + 1) * sizeof(int));
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);

	return 0;
}


int _merge_sort_non_guard_decremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num)
{
	*reverse_num = 0;
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	size_t left_reverse_num, right_reverse_num;
	left_card_num = right_card_num = 0;
	if (left_card_num > 1) _merge_sort_non_guard_decremental_get_reverse_num(cards, left_card_num, &left_reverse_num);
	if (right_card_num > 1) _merge_sort_non_guard_decremental_get_reverse_num(cards + mid, right_card_num, &right_reverse_num);
	*reverse_num += left_reverse_num + right_reverse_num;

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num * sizeof(int))) == NULL || (right_cards = malloc(right_card_num * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	long int cur;
	for (cur = 0; ; cur++){
		if (left <= left_most){
			if (right <= right_most){
				if (*left > *right){
					cards[cur] = *left++;
					if (cur >= left_card_num) *reverse_num += cur + 1 - left_card_num;
				}
				else{
					cards[cur] = *right++;
					if (cur < left_card_num) *reverse_num += left_card_num - cur;
				}
			}else{
				memcpy(cards + cur, left, (left_most - left + 1) * sizeof(int));
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + cur, right, (right_most - right + 1) * sizeof(int));
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);

	return 0;
}

int _merge_sort_guard_incremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num)
{
	*reverse_num = 0;
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	size_t left_reverse_num, right_reverse_num;
	left_reverse_num = right_reverse_num = 0;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_guard_incremental_get_reverse_num(cards, left_card_num, &left_reverse_num);
	if (right_card_num > 1) _merge_sort_guard_incremental_get_reverse_num(cards + mid, right_card_num, &right_reverse_num);
	*reverse_num += left_reverse_num + right_reverse_num;

	int *left_cards, *right_cards;
	if ((left_cards = malloc((left_card_num + 1) * sizeof(int))) == NULL || (right_cards = malloc((right_card_num + 1) * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right;
	left = left_cards;
	right = right_cards;
	long int cur;
	for (cur = 0; cur < left_card_num; cur++){
		if (*left < *right) cards[cur] = *left++;
		else{
			cards[cur] = *right++;
			*reverse_num += left_card_num - cur;
		}
	}
	for (; cur < card_num; cur++){
		if (*left < *right){
			cards[cur] = *left++;
			*reverse_num += cur /*+ 1*/ - left_card_num;
		}
		else cards[cur] = *right++;
	}
	free(left_cards);
	free(right_cards);
	return 0;
}

int _merge_sort_guard_decremental_get_reverse_num (int cards[], size_t card_num, size_t *reverse_num)
{
	*reverse_num = 0;
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	size_t left_reverse_num, right_reverse_num;
	left_card_num = right_card_num = 0;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_guard_decremental_get_reverse_num(cards, left_card_num, &left_reverse_num);
	if (right_card_num > 1) _merge_sort_guard_decremental_get_reverse_num(cards + mid, right_card_num, &right_reverse_num);
	*reverse_num += left_reverse_num + right_reverse_num;

	int *left_cards, *right_cards;
	if ((left_cards = malloc((left_card_num + 1) * sizeof(int))) == NULL || (right_cards = malloc((right_card_num + 1) * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right;
	left = left_cards;
	right = right_cards;
	long int cur;
	for (cur = 0; cur < left_card_num; cur++){
		if (*left > *right) cards[cur] = *left++;
		else{
			cards[cur] = *right++;
			*reverse_num += left_card_num - cur;
		}
	}
	for (; cur < card_num; cur++){
		if (*left > *right){
			cards[cur] = *left++;
			*reverse_num += cur + 1 - left_card_num;
		}
		else cards[cur] = *right++;
	}
	free(left_cards);
	free(right_cards);
	return 0;
}

int merge_sort_guard_get_reverse_num (int cards[], size_t card_num, int order, size_t *reverse_num)
{
	if (cards == NULL || card_num <= 0 || order == 0 || reverse_num == NULL) return 1;
	*reverse_num = 0;
	if (card_num == 1) return 0;
	if (order > 0) _merge_sort_guard_incremental_get_reverse_num(cards, card_num, reverse_num);
	else _merge_sort_guard_decremental_get_reverse_num(cards, card_num, reverse_num);
	return 0;
}

int _merge_sort_guard_incremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_guard_incremental(cards, left_card_num);
	if (right_card_num > 1) _merge_sort_guard_incremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc((left_card_num + 1) * sizeof(int))) == NULL || (right_cards = malloc((right_card_num + 1) * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	right_cards[right_card_num] = INT_MAX; //guard
	int *left, *right;
	left = left_cards;
	right = right_cards;
	for (size_t i = 0; i <= card_num - 1; i++){
		if (*left < *right) cards[i] = *left++;
		else cards[i] = *right++;
	}
	free(left_cards);
	free(right_cards);
	return 0;
}

int _merge_sort_guard_decremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_guard_decremental(cards, left_card_num);
	if (right_card_num > 1) _merge_sort_guard_decremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc((left_card_num + 1) * sizeof(int))) == NULL || (right_cards = malloc((right_card_num + 1) * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	left_cards[left_card_num] = INT_MAX; //guard
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
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
	return 0;
}

int merge_sort_guard (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num <= 0 || order == 0) return 1;
	else if (card_num == 1) return 0;
	if (order > 0) _merge_sort_guard_incremental(cards, card_num);
	else _merge_sort_guard_decremental(cards, card_num);
	return 0;
}

int _merge_sort_non_guard_incremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_non_guard_incremental(cards, left_card_num);
	if (right_card_num > 1) _merge_sort_non_guard_incremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num * sizeof(int))) == NULL || (right_cards = malloc(right_card_num * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	for (long int i = 0; ; i++){
		if (left <= left_most){
			if (right <= right_most){
				if (*left < *right) cards[i] = *left++;
				else cards[i] = *right++;
			}else{
				memcpy(cards + i, left, (left_most - left + 1) * sizeof(int));
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + i, right, (right_most - right + 1) * sizeof(int));
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);

	return 0;
}

int _merge_sort_non_guard_decremental (int cards[], size_t card_num)
{
	size_t left_card_num;
	size_t right_card_num;
	size_t mid = card_num / 2;
	left_card_num = mid;
	right_card_num = card_num - left_card_num;
	if (left_card_num > 1) _merge_sort_non_guard_incremental(cards, left_card_num);
	if (right_card_num > 1) _merge_sort_non_guard_incremental(cards + mid, right_card_num);

	int *left_cards, *right_cards;
	if ((left_cards = malloc(left_card_num * sizeof(int))) == NULL || (right_cards = malloc(right_card_num * sizeof(int))) == NULL) return 1;
	memcpy(left_cards, cards, left_card_num * sizeof(int));
	memcpy(right_cards, cards + mid, right_card_num * sizeof(int));
	int *left, *right, *left_most, *right_most;
	left = left_cards;
	right = right_cards;
	left_most = left_cards + left_card_num - 1;
	right_most = right_cards + right_card_num - 1;
	for (long int i = 0; ; i++){
		if (left <= left_most){
			if (right <= right_most){
				if (*left > *right) cards[i] = *left++;
				else cards[i] = *right++;
			}else{
				memcpy(cards + i, left, (left_most - left + 1) * sizeof(int));
				break;
			}
		}else{
			if (right <= right_most){
				memcpy(cards + i, right, (right_most - right + 1) * sizeof(int));
				break;
			}
			break;
		}
	}
	free(left_cards);
	free(right_cards);

	return 0;
}

int merge_sort_non_guard (int cards[], size_t card_num, int order)
{
	if (cards == NULL || card_num <= 0 || order == 0) return 1;
	else if (card_num == 1) return 0;
	if (order > 0) _merge_sort_non_guard_incremental(cards, card_num);
	else _merge_sort_non_guard_decremental(cards, card_num);
	return 0;
}
