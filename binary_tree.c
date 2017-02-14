//1.binary tree corresponding func

#include <stdlib.h>

//invoked by recursive lookup function
static void *_lookup_binary_tree_recursive (void *node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_value)(void *node_value, void *target_value))
{
	void *left_node, *right_node;
	void *node_value;
	int ret;

	node_value = get_node_value(node);
	if((ret = compare_value (node_value, target_value)) == 0) return node;
	else if(ret < 0){
		if ((left_node = get_left_node(node)) != NULL) return _lookup_binary_tree_recursive(left_node, target_value, get_left_node, get_right_node, get_node_value, compare_value);
		else return NULL;
	}
	else{
		if ((right_node = get_right_node(node)) != NULL) return _lookup_binary_tree_recursive(right_node, target_value, get_left_node, get_right_node, get_node_value, compare_value);
		else return NULL;

	}
}

//recursive version of lookup(binary tree is in order, 
//given pointer to function to get pointer of left and
//right node of node, pointer to function to get value of 
//node, pointer to function to compare node value
void *lookup_binary_tree_recursive (void *node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_value)(void *node_value, void *target_value))
{
	if (node == NULL || target_value == NULL || get_left_node == NULL || get_right_node == NULL || get_node_value == NULL || compare_value == NULL) return NULL;
	return _lookup_binary_tree_recursive (node, target_value, get_left_node, get_right_node, get_node_value, compare_value);
}

//loop version of lookup(binary tree is in order), 
//args are the same as recursive version
void *lookup_binary_tree_loop (void *start_node, void *target_value, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void *get_node_value(void *node), int (*compare_value)(void *node_value, void *target_value))
{
	void *node;
	void *node_value;
	int ret;

	if (start_node == NULL || target_value == NULL || get_left_node == NULL || get_right_node == NULL || get_node_value == NULL || compare_value == NULL) return NULL;
	node = start_node;
	while (1){

		node_value = get_node_value(node);
		if((ret = compare_value (node_value, target_value)) == 0) return node;
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

static void _traverse_binary_tree_recursive (void *node, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void traverse_func(void *node))
{
	void *left_node, *right_node;
	if ((left_node = get_left_node(node)) != NULL) _traverse_binary_tree_recursive (left_node, get_left_node, get_right_node, traverse_func);
	(*traverse_func)(node);
	if ((right_node = get_right_node(node)) != NULL) _traverse_binary_tree_recursive (right_node, get_right_node, get_right_node, traverse_func);
}

int traverse_binary_tree_recursive (void *root, void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void traverse_func(void *node))
{
	if (root == NULL || get_left_node == NULL || get_right_node == NULL || traverse_func == NULL) return -1;
	_traverse_binary_tree_recursive(root, get_left_node, get_right_node, traverse_func);
	return 0;
}

int _insert_value_into_binary_tree_recursive(void *node, void *insert_value, void *(*create_node)(void *value), void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), void (*set_left_node)(void *node), void (*set_right_node)(void *node), int (*compare_value)(void *node_value, void *target_value), void *(*get_node_value)(void *node))
{
	void *new_node, *left_node, *right_node;
	void *current_value;
	int ret;
	current_value = get_node_value(node);
	if ((ret = compare_value(current_value, insert_value)) == 0) return 0; //discard value that already exist in binary tree
	if (ret < 0){
		if ((left_node = get_left_node(node)) == NULL){
			if((new_node = create_node(insert_value)) == NULL) return 1;
			set_left_node(node, new_node);
			return 0;
		}
		else return _insert_value_into_binary_tree_recursive(left_node, insert_value, create_node, get_left_node, get_right_node, compare_value, create_node, get_node_value);
	}
	else{
		if ((right_node = get_right_node(node)) == NULL){
			if((new_node = create_node(insert_value)) == NULL) return 1;
			set_right_node(node, new_node);
			return 0;
		}
		else return _insert_value_into_binary_tree_recursive(right_node, insert_value, create_node, get_left_node, get_right_node, compare_value, get_node_value);
	}
}

int insert_value_into_binary_tree_recursive(void *node, void *insert_value, void *(*create_node)(void *value), void *(*get_left_node)(void *node), void *(*get_right_node)(void *node), int (*compare_value)(void *node_value, void *target_valu), void *(*get_node_value)(void *node))
{
	void *new_node;
	if (insert_value == NULL || create_node == NULL || get_left_node == NULL || get_right_node == NULL || compare_value == NULL || create_node == NULL) return -1;
	if (node == NULL){
		if((new_node = create_node(insert_value)) == NULL) return 1;
		else return 0;
		}
	else return _insert_value_into_binary_tree_recursive(node, insert_value, create_node, get_left_node, get_right_node, compare_value, get_node_value);
}
