#include "test_sort_get_reverse_num.h"

long clock_ticks;

int main (void)
{
#ifdef CLK_TCK
	clock_ticks = CLK_TCK;
#else
	#ifdef _SC_CLK_TCK
	clock_ticks = sysconf(_SC_CLK_TCK);
	if (clock_ticks < 0) p_err("sysconf failed.");
	#else
	err("couldn't get clock ticks.");
	#endif
#endif

	int *cards = NULL;
	int *orig_cards = NULL;
	size_t card_num;
#define FUNC_NUM 5
	int(*funcs[FUNC_NUM])(int[], size_t, int, size_t*);
	funcs[0] = merge_sort_non_guard_get_reverse_num;
	funcs[1] = merge_sort_guard_get_reverse_num;
	funcs[2] = merge_sort_insert_sort_guard_get_reverse_num;
	funcs[3] = merge_sort_insert_sort_non_guard_get_reverse_num;
	funcs[4] = insert_sort_get_reverse_num;

	int last_card_num;
	for (card_num = 1000, last_card_num = 0; card_num < 90000000/*MAX_CARD_NUM*/; ){
		if ((cards = realloc(cards, card_num * sizeof(int))) == NULL || (orig_cards = realloc(orig_cards, card_num * sizeof(int))) == NULL){
			fprintf(stderr, "malloc for card_num:%zd failed.\n", card_num);
			exit(1);
		}
		for (long int i = last_card_num; i < card_num; i++) orig_cards[i] = i;
		memcpy(cards, orig_cards, card_num * sizeof(int));
		if (randomize_cards(cards, card_num)) err("randomize_cards func failed.");
		//print_randomize_cards(cards, card_num);
		//print_original_cards(orig_cards, card_num);
		printf("card_num:%zd\n", card_num);
		fflush(stdout);
		various_sort_cards (cards, orig_cards, card_num, funcs, FUNC_NUM - 1);
		last_card_num = card_num;
		if (card_num < 128) card_num++;
		else card_num *= 5;
		printf("\n\n");
	}
}

void print_sort_fatal_err_msg(int cur_func)
{
	if (cur_func == 0) printf("err: merge sort non guard\n");
	else if (cur_func == 1) printf("err: merge sort guard\n");
	else if (cur_func == 2) printf("err: merge sort insert sort guard\n");
	else if (cur_func == 3) printf("err: merge sort insert sort non guard\n");
	else if (cur_func == 4) printf("err: insert sort\n");
}

void print_success_msg (int cur_func, double elapsed, size_t reverse_num)
{
	if (cur_func == 0) printf("success: merge sort non guard, reverse num:%zd, time used:%f", reverse_num, elapsed);
	else if (cur_func == 1) printf("success: merge sort guard, reverse num:%zd, time used:%f", reverse_num, elapsed);
	else if (cur_func == 2) printf("success: merge sort insert sort guard, reverse num:%zd, time used:%f", reverse_num, elapsed);
	else if (cur_func == 3) printf("success: merge sort insert sort non guard, reverse num:%zd, time used:%f", reverse_num, elapsed);
	else if (cur_func == 4) printf("success: insert sort, reverse num:%zd, time used:%f", reverse_num, elapsed);
}

void print_sort_func_fail_msg (int cur_func)
{
	if (cur_func == 0) printf("failed: merge sort non guard.\n");
	else if (cur_func == 1) printf("failed: merge sort guard.\n");
	else if (cur_func == 2) printf("failed: merge sort insert sort guard.\n");
	else if (cur_func == 3) printf("failed: merge sort insert sort non guard.\n");
	else if (cur_func == 4) printf("failed: insert sort.\n");
}

void print_sort_func_return_err (int cur_func, int ret)
{
	if (cur_func == 0) printf("error: merge sort non guard return, ret:%d\n", ret);
	else if (cur_func == 1) printf("error: merge sort guard return, ret:%d\n", ret);
	else if (cur_func == 2) printf("error: merge sort insert sort guard return, ret:%d\n", ret);
	else if (cur_func == 3) printf("error: merge sort insert sort non guard return, ret:%d\n", ret);
	else if (cur_func == 4) printf("error: insert sort return, ret:%d\n", ret);
}

int get_process_runtime_ticks (clock_t *ticks)
{
	struct tms buf;
	if (times(&buf) == (clock_t)-1) return 1;
	*ticks = buf.tms_utime + buf.tms_stime;
	return 0;
}

int check_sort_result (int cards[], int orig_cards[], size_t card_num)
{
	int max = card_num - 1;
	for (long int i = 0; i <= max; i++){
		if (cards[i] != orig_cards[i]) return 1;
	}
	return 0;
}

void print_cards (int cards[], size_t card_num)
{
	printf("cards:");
	for (long int i = 0; i < card_num; i++) printf(" %d", cards[i]);
	printf("\n");
}
void print_original_cards (int cards[], size_t card_num)
{
	printf("original ");
	print_cards(cards, card_num);
}

void process_result_of_child (int status, int cards[], size_t card_num, int cur_func)
{
	if (WIFSIGNALED(status)){
		fprintf(stderr, "signal num:%d\n", WTERMSIG(status));
		print_sort_fatal_err_msg(cur_func);
	}
}

void sort_cards (int cards[], int orig_cards[], size_t card_num, int(*func)(int[], size_t, int, size_t*), int cur_func)
{
	pid_t pid;
	if ((pid = fork()) == -1) p_err("fork failed.");
	if (pid == 0){
		int ret;
		double elapsed;
		clock_t before_sort_ticks, after_sort_ticks;
		size_t reverse_num;
		if (get_process_runtime_ticks (&before_sort_ticks)) err("times func failed.");
		ret = (*func)(cards, card_num, 1, &reverse_num);
		if (get_process_runtime_ticks (&after_sort_ticks)) err("times func failed.");
		if (ret) print_sort_func_return_err(cur_func, ret);
		else{
			if (check_sort_result (cards, orig_cards, card_num) == 0){
				elapsed = 1.0 * (after_sort_ticks - before_sort_ticks) / clock_ticks;
				print_success_msg(cur_func, elapsed, reverse_num);
				if (print_resource_usage()) p_err("getrusage failed.");
			}
			else{
				print_sort_func_fail_msg (cur_func);
				print_cards(cards, card_num);
			}
		}
		exit(ret);
	}else{//parent
		int status;
		if (waitpid(pid, &status, 0) == -1) p_err("wait failed.");
		process_result_of_child (status, cards, card_num, cur_func);
	}
}

void various_sort_cards (int cards[], int orig_cards[], size_t card_num, int(*funcs[])(int[], size_t, int, size_t*), size_t func_num)
{
	for (int cur_func = 0; cur_func < func_num; cur_func++){
		sort_cards(cards, orig_cards, card_num, funcs[cur_func], cur_func);
	}
}

int init_random_number (void)
{
	struct timespec ts;
	unsigned int rand;
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return 1;
	rand = ts.tv_sec * ts.tv_nsec + ts.tv_sec + ts.tv_nsec;
	srand(rand);
	return 0;
}

int get_random_number (int max)
{
	double f;
	f = 1.0 * max * rand() / (RAND_MAX + 1LL);

	return (int)f;
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
	if (init_random_number()) return 1;
	for (long int i = 0; i <= max; i++){
		do{
			previous1 = pos1;
			previous2 = pos2;
			pos1 = get_random_number(card_num);
			pos2 = get_random_number(card_num);
			if (pos1 > card_num - 1 || pos2 > card_num - 1) continue;
		}while (pos1 == pos2 || (pos1 == previous1 && pos2 == previous2) || (pos1 == previous2 && pos2 == previous1));
		swap_int(&cards[pos1], &cards[pos2]);
	}
	return 0;
}

void print_randomize_cards (int cards[], size_t card_num)
{
	printf("randomize ");
	print_cards(cards, card_num);
}

int print_resource_usage(void)
{
	struct rusage res;
	if (getrusage(RUSAGE_SELF, &res) == -1) return 1;
	if (res.ru_maxrss <= 1024) printf(" usage: resident:%ld KB\n", res.ru_maxrss);
	else if (res.ru_maxrss <= 1024 * 1024L)printf(" usage: resident:%.3f MB\n", res.ru_maxrss / 1024.0);
	else printf(" usage: resident:%.3f GB\n", res.ru_maxrss / (1024.0 * 1024));

	return 0;
}
