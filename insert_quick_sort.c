#include "insert_quick_sort.h"

int *_binary_search_incremental (int cards[], size_t card_num, int target)
{
	int *left, *right, *mid, *pos;
	pos = NULL;
	left = cards, right = left + (card_num - 1);
	if (target < *left) return left;
	if (target > *right) return right + 1;
	for (; left < right; ){
		mid = left + (right - left) / 2;
		if (*mid == target) return mid;
		else if (target < *mid){
			if (left == right - 1) return right;
			right = mid;
			continue;
		}else{
			if (left == right - 1) return right;
			left = mid;
			continue;
		}
	}
	return NULL;
}

int *_binary_search_decremental (int cards[], size_t card_num, int target)
{
	int *left, *right, *mid, *pos;
	pos = NULL;
	left = cards, right = left + (card_num - 1);
	if (target < *right) return right + 1;
	if (target > *left) return left;
	for (; left < right; ){
		mid = left + (right - left) / 2;
		if (*mid == target) return mid;
		else if (target > *mid){
			if (left == right - 1) return left;
			right = mid;
			continue;
		}else{
			if (left == right - 1) return left;
			left = mid;
			continue;
		}
	}
	return NULL;
}

int _insert_quick_sort_incremental (int cards[], size_t card_num)
{
	if (cards[0] > cards[1]) swap_int(&cards[0], &cards[1]);
	if (card_num == 2) return 0;
	for (size_t i = 2; i <= card_num - 1; i++){
		int *pos;
		if ((pos = _binary_search_incremental(cards, i, cards[i])) == NULL){
			return 1;
		}
		int tmp = cards[i];
		if (pos != &cards[i]) memmove(pos + 1, pos, (i - (pos - cards)) * sizeof(int));
		*pos = tmp;
	}
	return 0;
}

int _insert_quick_sort_decremental (int cards[], size_t card_num)
{
	if (cards[0] < cards[1]) swap_int(&cards[0], &cards[1]);
	if (card_num == 2) return 0;
	for (size_t i = 2; i <= card_num - 1; i++){
		int *pos;
		if ((pos = _binary_search_decremental(cards, i, cards[i])) == NULL){
			return 1;
		}
		int tmp = cards[i];
		if (pos != &cards[i]) memmove(pos + 1, pos, (i - (pos - cards)) * sizeof(int));
		*pos = tmp;
	}
	return 0;
}

int insert_quick_sort (int cards[], size_t card_num, int sort_order)
{
	if (cards == NULL ||card_num <= 0 || sort_order == 0) return 1;
	if (card_num == 1) return 0;
	if (sort_order > 0){
		if (_insert_quick_sort_incremental(cards, card_num)) return 2;
	}
	else if (_insert_quick_sort_decremental(cards, card_num)) return 3;
	return 0;
}


/* test part */
/*#include <stdio.h>
#include "assist.h"
int get_random_number (int *num, int max)
{
	struct timespec ts;
	unsigned int rand;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return 1;
	rand = ts.tv_sec * ts.tv_nsec + ts.tv_sec + ts.tv_nsec;
	srandom(rand);
	double f;
	f = 1.0 * max * random() / (RAND_MAX + 1LL);
	*num = f;

	return 0;
}

int randomize_cards (int cards[], size_t card_num)
{
	if (card_num == 1) return 0;
	else if (card_num == 2){
		swap_int(&cards[0], &cards[1]);
		return 0;
	}
	static int previous1, previous2;
	static int pos1, pos2;
	long max = card_num / 2;
	for (long int i = 0; i <= max; i++){
		do{
			previous1 = pos1;
			previous2 = pos2;
			if (get_random_number(&pos1, card_num)) return 1;
			if (get_random_number(&pos2, card_num)) return 1;
			if (pos1 > card_num - 1 || pos2 > card_num - 1) continue;
		}while (pos1 == pos2 || (pos1 == previous1 && pos2 == previous2) || (pos1 == previous2 && pos2 == previous1));
		swap_int(&cards[pos1], &cards[pos2]);
	}
	return 0;
}

void print_cards (int cards[], size_t card_num)
{
	printf("cards:");
	for (long int i = 0; i < card_num; i++) printf(" %d", cards[i]);
	printf("\n");
}

int main (void)
{
	int *cards = NULL;
	int *orig_cards = NULL;
	size_t card_num = 80;
	if ((cards = malloc(sizeof(int) * card_num)) == NULL || (orig_cards = malloc(sizeof(int) * card_num)) == NULL){
		fprintf(stderr, "malloc failed.");
		return 1;
	}
	for (long i = 0; i < card_num; i++){
		orig_cards[i] = i;
		cards[i] = i;
	}
	if (randomize_cards (cards, card_num)) err("randomize failed.");
	printf("original ");
	print_cards(orig_cards, card_num);
	printf("randomized  ");
	print_cards(cards, card_num);
	if (insert_quick_sort(cards, card_num, 1)) err("insert sort failed.");
	for (long i = 0; i < card_num; i++){
		if (cards[i] != orig_cards[i]){
			printf("sort failed, cards[%ld]:%d, orig_cards[%ld]:%d.\n", i, cards[i], i, orig_cards[i]);
			printf("sorted ");
			print_cards(cards, card_num);
			return 1;
		}
	}
	printf("sort success.\n");

	return 0;
}
*/
