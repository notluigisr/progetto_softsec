static struct db_sys_list *_db_rule_gen_32(const struct arch_def *arch,
					   const struct db_api_rule_list *rule)
{
	unsigned int iter;
	struct db_sys_list *s_new;
	const struct db_api_arg *chain = rule->args;
	struct db_arg_chain_tree *c_iter = NULL, *c_prev = NULL;
	bool tf_flag;

	s_new = zmalloc(sizeof(*s_new));
	if (s_new == NULL)
		return NULL;
	s_new->num = rule->syscall;
	s_new->valid = true;
	
	for (iter = 0; iter < ARG_COUNT_MAX; iter++) {
		if (chain[iter].valid == 0)
			continue;

		
		if (!_db_arg_cmp_need_lo(&chain[iter]))
			continue;

		c_iter = zmalloc(sizeof(*c_iter));
		if (c_iter == NULL)
			goto gen_32_failure;
		c_iter->arg = chain[iter].arg;
		c_iter->arg_offset = arch_arg_offset(arch, c_iter->arg);
		c_iter->op = chain[iter].op;
		
		c_iter->mask = chain[iter].mask;
		c_iter->datum = chain[iter].datum;

		
		if (c_prev != NULL) {
			if (tf_flag)
				c_prev->nxt_t = _db_node_get(c_iter);
			else
				c_prev->nxt_f = _db_node_get(c_iter);
		} else
			s_new->chains = _db_node_get(c_iter);
		s_new->node_cnt++;

		
		switch (c_iter->op) {
		case SCMP_CMP_NE:
			c_iter->op = SCMP_CMP_EQ;
			tf_flag = false;
			break;
		case SCMP_CMP_LT:
			c_iter->op = SCMP_CMP_GE;
			tf_flag = false;
			break;
		case SCMP_CMP_LE:
			c_iter->op = SCMP_CMP_GT;
			tf_flag = false;
			break;
		default:
			tf_flag = true;
		}

		
		_db_node_mask_fixup(c_iter);

		c_prev = c_iter;
	}
	if (c_iter != NULL) {
		
		if (tf_flag) {
			c_iter->act_t_flg = true;
			c_iter->act_t = rule->action;
		} else {
			c_iter->act_f_flg = true;
			c_iter->act_f = rule->action;
		}
	} else
		s_new->action = rule->action;

	return s_new;

gen_32_failure:
	
	_db_tree_put(&s_new->chains);
	free(s_new);
	return NULL;
}