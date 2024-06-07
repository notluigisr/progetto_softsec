static unsigned int _db_tree_put(struct db_arg_chain_tree **tree)
{
	int cnt = 0;
	struct db_arg_chain_tree *node, *prev, *next;

	if (tree == NULL || *tree == NULL)
		return 0;
	node = *tree;

	while (node->lvl_nxt != NULL)
		node = node->lvl_nxt;

	while (node != NULL) {
		prev = node->lvl_prv;
		next = node->lvl_nxt;

		cnt += _db_tree_put(&node->nxt_t);
		cnt += _db_tree_put(&node->nxt_f);
		if (--(node->refcnt) == 0) {
			
			if (prev)
				prev->lvl_nxt = next;
			if (next)
				next->lvl_prv = prev;

			
			if (prev != NULL)
				*tree = prev;
			else
				*tree = next;

			
			free(node);
			cnt++;
		}

		
		node = prev;
	}

	return cnt;
}