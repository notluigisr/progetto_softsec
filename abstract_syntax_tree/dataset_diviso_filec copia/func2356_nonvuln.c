static __init int ftrace_test_event_filter(void)
{
	int i;

	printk(KERN_INFO "STR");

	for (i = 0; i < DATA_CNT; i++) {
		struct event_filter *filter = NULL;
		struct test_filter_data_t *d = &test_filter_data[i];
		int err;

		err = create_filter(&event_ftrace_test_filter, d->filter,
				    false, &filter);
		if (err) {
			printk(KERN_INFO
			       "STR",
			       d->filter, err);
			__free_filter(filter);
			break;
		}

		
		mutex_lock(&event_mutex);
		
		preempt_disable();
		if (*d->not_visited)
			update_pred_fn(filter, d->not_visited);

		test_pred_visited = 0;
		err = filter_match_preds(filter, &d->rec);
		preempt_enable();

		mutex_unlock(&event_mutex);

		__free_filter(filter);

		if (test_pred_visited) {
			printk(KERN_INFO
			       "STR",
			       d->filter);
			break;
		}

		if (err != d->match) {
			printk(KERN_INFO
			       "STR",
			       d->filter, d->match);
			break;
		}
	}

	if (i == DATA_CNT)
		printk(KERN_CONT "STR");

	return 0;
}