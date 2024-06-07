static struct db_arg_chain_tree *_db_tree_get(struct db_arg_chain_tree *tree)
{
	struct db_arg_chain_tree *iter;

	if (tree->nxt_t) {
		iter = tree->nxt_t;
		while (iter->lvl_prv != NULL)
			iter = iter->lvl_prv;
		do {
			_db_tree_get(iter);
			iter = iter->lvl_nxt;
		} while (iter != NULL);
	}

	if (tree->nxt_f) {
		iter = tree->nxt_f;
		while (iter->lvl_prv != NULL)
			iter = iter->lvl_prv;
		do {
			_db_tree_get(iter);
			iter = iter->lvl_nxt;
		} while (iter != NULL);
	}

	return _db_node_get(tree);
}