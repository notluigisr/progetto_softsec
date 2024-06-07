static unsigned int _db_tree_remove(struct db_arg_chain_tree **tree,
				    struct db_arg_chain_tree *node)
{
	int cnt = 0;
	struct db_arg_chain_tree *c_iter;

	if (tree == NULL || *tree == NULL || node == NULL)
		return 0;

	c_iter = *tree;
	while (c_iter->lvl_prv != NULL)
		c_iter = c_iter->lvl_prv;

	do {
		
		if (c_iter == node)
			goto remove;

		
		cnt += _db_tree_remove(&(c_iter->nxt_t), node);
		cnt += _db_tree_remove(&(c_iter->nxt_f), node);

		
		if (_db_chain_zombie(c_iter))
			goto remove;

		
		c_iter = c_iter->lvl_nxt;
	} while (c_iter != NULL && cnt == 0);

	return cnt;

remove:
	
	if (c_iter == *tree) {
		if (c_iter->lvl_prv != NULL)
			*tree = c_iter->lvl_prv;
		else
			*tree = c_iter->lvl_nxt;
	}

	
	if (c_iter->lvl_prv)
		c_iter->lvl_prv->lvl_nxt = c_iter->lvl_nxt;
	if (c_iter->lvl_nxt)
		c_iter->lvl_nxt->lvl_prv = c_iter->lvl_prv;
	c_iter->lvl_prv = NULL;
	c_iter->lvl_nxt = NULL;

	
	cnt += _db_tree_put(&c_iter);

	return cnt;
}