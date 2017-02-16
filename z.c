struct tree{
	struct tree *left;
	struct tree *right;
}

int check_balance (void *node)
{
	if (node == NULL) return 0;
	if (node->left == NULL) left_depth = 0;
	else left_depth = check_balance(tree->left);
	if (node->right == NULL) right_depth = 0;
	else right_depth = check_balance(tree->right);
	if (-1 < left_depth - right_depth < 1) return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
	return -1;
}
