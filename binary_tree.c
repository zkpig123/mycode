#include <stdlib.h>

void *_binary_tree_lookup_recursive (void *node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_node_value)(void *node_value, void *target_value))
{
	void *left_node, *right_node;
	void *node_value;
	int ret;

	node_value = get_node_value(node);
	if((ret = compare_node_value (node_value, target_value)) == 0) return node;
	else if(ret < 0){
		if ((left_node = get_left_node(node)) != NULL) return _binary_tree_lookup_recursive(left_node, target_value, get_left_node, get_right_node, get_node_value, compare_node_value);
		else return NULL;
	}
	else{
		if ((right_node = get_right_node(node)) != NULL) return _binary_tree_lookup_recursive(right_node, target_value, get_left_node, get_right_node, get_node_value, compare_node_value);
		else return NULL;

	}
}

void *binary_tree_lookup_recursive (void *node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_node_value)(void *node_value, void *target_value))
{
	if (node == NULL || target_value == NULL || get_left_node == NULL || get_right_node == NULL || get_node_value == NULL || compare_node_value == NULL) return NULL;
	return _binary_tree_lookup_recursive (node, target_value, get_left_node, get_right_node, get_node_value, compare_node_value);
}

void *binary_tree_lookup_loop (void *node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_node_value)(void *node_value, void *target_value))
{
	void *left_node, *right_node;
	void *node_value;
	int ret;

	if (node == NULL || target_value == NULL || get_left_node == NULL || get_right_node == NULL || get_node_value == NULL || compare_node_value == NULL) return NULL;
	while (1){

		node_value = get_node_value(node);
		if((ret = compare_node_value (node_value, target_value)) == 0) return node;
		else if(ret < 0){
				if ((node = get_left_node(node)) != NULL) continue;
				else return NULL;
			}
		else{
			if ((node = get_right_node(node)) != NULL) continue;
			else return NULL;

		}
	}
	return NULL; //should never get here
}
