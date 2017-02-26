#include <stdlib.h>
#include <string.h>

void _insert_sort_decremental (int cards[], size_t card_num)
{
	if (card_num <= 1) return;
	for (size_t i = 1; i <= card_num - 1; i++){
		int *left, *right, *mid, *pos;
		for (left = cards, right = cards + i - 1; ; ){
			if (left + 1 == right){
				if (*left >= cards[i]){
					pos = left;
					break;
				}else if (*right <= cards[i]){
					pos = right + 1;
					break;
				}else{
					pos = right;
					break;
				}
			}
			mid = left + card_num / 2;
			if (*mid == cards[i]){
				pos = mid;
				break;
			}else if (*mid < cards[i]){
				left = mid;
				continue;
			}else{
				right = mid;
				continue;
			}
			int tmp = cards[i];
			memmove(pos + 1, pos, i - (pos - cards));
			*pos = tmp;
		}
	}
}

void _insert_sort_incremental (int cards[], size_t card_num)
{
	if (card_num <= 1) return;
	for (size_t i = 1; i <= card_num - 1; i++){
		int *left, *right, *mid, *pos;
		for (left = cards, right = cards + i - 1; ; ){
			if (left + 1 == right){
				if (*left >= cards[i]){
					pos = left;
					break;
				}else if (*right <= cards[i]){
					pos = right + 1;
					break;
				}else{
					pos = right;
					break;
				}
			}
			mid = left + card_num / 2;
			if (*mid == cards[i]){
				pos = mid;
				break;
			}else if (*mid < cards[i]){
				left = mid;
				continue;
			}else{
				right = mid;
				continue;
			}
			int tmp = cards[i];
			memmove(pos + 1, pos, i - (pos - cards));
			*pos = tmp;
		}
	}
}

int insert_sort (int cards[], size_t card_num, int sort_order)
{
	if (cards == NULL ||card_num <= 0 || sort_order == 0) return -1;
	if (card_num == 1) return 0;
	if (sort_order > 0) _insert_sort_incremental(cards, card_num);
	else _insert_sort_decremental(cards, card_num);
	return 0;
}
