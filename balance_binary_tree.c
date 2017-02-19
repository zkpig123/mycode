#include <stdlib.h>

int is_balance (void *node, size_t *depth, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node))
{
	void *left_child, *right_child;
	size_t left_depth, right_depth;
	int left_is_balance, right_is_balance;
	ssize_t diff;
	if (node == NULL){
		*depth = 0;
		return 0;
	}
	if ((left_child = get_left_node(node)) == NULL) left_depth = 0;
	else left_is_balance = is_balance(left_child, &left_depth, get_left_node, get_right_node);
	if ((right_child = get_right_node(node)) == NULL) right_depth = 0;
	else right_is_balance = is_balance(right_child, &right_depth, get_left_node, get_right_node);
	*depth = left_depth > right_depth ? left_depth : right_depth;
	diff = left_depth - right_depth;
	if (diff < 0) diff = -diff;
	if (left_is_balance && right_is_balance && diff <= 1) return 1;
	else return 0;
}
