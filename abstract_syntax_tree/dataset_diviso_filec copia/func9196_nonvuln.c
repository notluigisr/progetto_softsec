int jbd2_journal_get_undo_access(handle_t *handle, struct buffer_head *bh)
{
	int err;
	struct journal_head *jh = jbd2_journal_add_journal_head(bh);
	char *committed_data = NULL;

	JBUFFER_TRACE(jh, "STR");

	
	err = do_get_write_access(handle, jh, 1);
	if (err)
		goto out;

repeat:
	if (!jh->b_committed_data) {
		committed_data = jbd2_alloc(jh2bh(jh)->b_size, GFP_NOFS);
		if (!committed_data) {
			printk(KERN_EMERG "STR",
				__func__);
			err = -ENOMEM;
			goto out;
		}
	}

	jbd_lock_bh_state(bh);
	if (!jh->b_committed_data) {
		
		JBUFFER_TRACE(jh, "STR");
		if (!committed_data) {
			jbd_unlock_bh_state(bh);
			goto repeat;
		}

		jh->b_committed_data = committed_data;
		committed_data = NULL;
		memcpy(jh->b_committed_data, bh->b_data, bh->b_size);
	}
	jbd_unlock_bh_state(bh);
out:
	jbd2_journal_put_journal_head(jh);
	if (unlikely(committed_data))
		jbd2_free(committed_data, bh->b_size);
	return err;
}