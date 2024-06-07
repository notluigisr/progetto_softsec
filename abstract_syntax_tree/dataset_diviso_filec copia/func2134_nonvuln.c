static struct css_set *css_task_iter_next_css_set(struct css_task_iter *it)
{
	struct list_head *l;
	struct cgrp_cset_link *link;
	struct css_set *cset;

	lockdep_assert_held(&css_set_lock);

	
	if (it->tcset_pos) {
		l = it->tcset_pos->next;

		if (l != it->tcset_head) {
			it->tcset_pos = l;
			return container_of(l, struct css_set,
					    threaded_csets_node);
		}

		it->tcset_pos = NULL;
	}

	
	l = it->cset_pos;
	l = l->next;
	if (l == it->cset_head) {
		it->cset_pos = NULL;
		return NULL;
	}

	if (it->ss) {
		cset = container_of(l, struct css_set, e_cset_node[it->ss->id]);
	} else {
		link = list_entry(l, struct cgrp_cset_link, cset_link);
		cset = link->cset;
	}

	it->cset_pos = l;

	
	if (it->flags & CSS_TASK_ITER_THREADED) {
		if (it->cur_dcset)
			put_css_set_locked(it->cur_dcset);
		it->cur_dcset = cset;
		get_css_set(cset);

		it->tcset_head = &cset->threaded_csets;
		it->tcset_pos = &cset->threaded_csets;
	}

	return cset;
}