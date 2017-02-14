//1.reverse unidirectional link list using both recursive method and loop method, given pointer to current
//list, pointer to function that get next item from current 
//item, pointer to function that set next item of current
//item
//2.use reverse_list_recursive or rever_list_loop, don't use _reverse_list directly
#include <stdlib.h>

void *_reverse_list (void *previous_item, void *current_item, void *(*get_next_item)(void *item), int (*set_next_item)(void *item, void *desired_next_item))
{
	void *next_item;
	if (current_item == NULL) return NULL;
	next_item = get_next_item(current_item);
	set_next_item (current_item, previous_item);
	if (next_item == NULL) return current_item;
	else return _reverse_list(current_item, next_item, get_next_item, set_next_item);
}

void *reverse_list_recursive (void *list, void *(*get_next_item)(void *item), int (*set_next_item)(void *item, void *desired_next_item))
{
	void *next;
	if (list == NULL) return NULL;
	next = get_next_item (list);
	if (next == NULL) return list;
	else return _reverse_list (list, next, get_next_item, set_next_item);
}
