//link list corresponding function
#include <stdlib.h>

//invoked by reverse function
static void *_reverse_list_recursive (void *previous_item, void *current_item, void *(*get_next_item)(void *item), int (*set_next_item)(void *item, void *desired_next_item))
{
	void *next_item;
	if (current_item == NULL) return NULL;
	next_item = get_next_item(current_item);
	set_next_item (current_item, previous_item);
	if (next_item == NULL) return current_item;
	else return _reverse_list_recursive(current_item, next_item, get_next_item, set_next_item);
}

//reverse unidirectional link list using recursive method,
//given pointer to current list, pointer to function that
//get next item from current item, pointer to function
//that set next item of current item, return pointer to 
//first item
void *reverse_list_recursive (void *list, void *(*get_next_item)(void *item), int (*set_next_item)(void *item, void *desired_next_item))
{
	void *next;

	if (list == NULL || get_next_item == NULL || set_next_item == NULL) return NULL;
	if (list == NULL) return NULL;
	next = get_next_item (list);
	if (next == NULL) return list;
	else return _reverse_list_recursive (list, next, get_next_item, set_next_item);
}

//reverse link list using loop, args are the same as recursive
//version, return pointer to first item
void *reverse_list_loop (void *list, void *(*get_next_item)(void *item), int (*set_next_item)(void *item, void *desired_next_item))
{
	void *next_item, *current_item, *previous_item;
	if (list == NULL || get_next_item == NULL || set_next_item == NULL) return NULL;
	previous_item = NULL;
	current_item = list;
	while (1){

		next_item = get_next_item(current_item);
		set_next_item (current_item, previous_item);
		if (next_item == NULL) return current_item;
		else current_item = next_item;
	}
}
