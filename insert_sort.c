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

int insert_sort (int cards[], size_t card_num, int sort_order)
{
	if (cards == NULL ||card_num <= 0 || sort_order == 0) return -1;
	if (card_num == 1) return 0;
	if (sort_order > 0) _insert_sort_incremental(cards, card_num);
	else _insert_sort_decremental(cards, card_num);
	return 0;
}
