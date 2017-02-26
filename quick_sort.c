#include "quick_sort.h"

void swap_int (int *n1, int *n2)
{
    if (n1 == n2) return;
	*n1 = *n1 ^ *n2;
	*n2 = *n1 ^ *n2;
	*n1 = *n1 ^ *n2;
}

int _quick_sort_from_side_incremental (int cards[], size_t card_num)
{
	size_t base;
	if (card_num > 5){
		/*struct timespec ts;
		unsigned int rand;
		if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return 1;
		rand = ts.tv_sec * ts.tv_nsec + ts.tv_sec + ts.tv_nsec;
		srandom((unsigned int)rand);*/
		base = random() % card_num;
	}
	else base = 0;
	if (base) swap_int(cards, &cards[base]); //swap cards[0] and cards[base-1]
	size_t base_final_pos = 0;
	for (size_t i = 1; i <= card_num - 1; i++){
		if (cards[i] < cards[0]){
			base_final_pos++;
			swap_int(&cards[base_final_pos], &cards[i]);
		}
	}
	if (base_final_pos) swap_int(&cards[0], &cards[base_final_pos]);
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
	size_t base;
	if (card_num > 5){
		time_t cur_time = time(NULL);
		if (cur_time == (time_t)-1) return 1;
		srandom((unsigned int)cur_time);
		base = random() % card_num;
	}
	else base = 0;

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

/* test part */
/*
#include <stdio.h>
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
	if ((cards = malloc(sizeof(int) * card_num)) == NULL || (orig_cards = malloc(sizeof(int) * card_num)) == NULL) err("malloc failed.");
	for (long i = 0; i < card_num; i++){
		orig_cards[i] = i;
		cards[i] = i;
	}
	if (randomize_cards (cards, card_num)) err("randomize failed.");
	printf("original ");
	print_cards(orig_cards, card_num);
	printf("randomized  ");
	print_cards(cards, card_num);
	if (quick_sort_from_side(cards, card_num, 1)) err("quick sort failed.");
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
