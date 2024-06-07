static int eb_reserve(struct i915_execbuffer *eb)
{
	const unsigned int count = eb->buffer_count;
	struct list_head last;
	struct i915_vma *vma;
	unsigned int i, pass;
	int err;

	

	pass = 0;
	err = 0;
	do {
		list_for_each_entry(vma, &eb->unbound, exec_link) {
			err = eb_reserve_vma(eb, vma);
			if (err)
				break;
		}
		if (err != -ENOSPC)
			return err;

		
		INIT_LIST_HEAD(&eb->unbound);
		INIT_LIST_HEAD(&last);
		for (i = 0; i < count; i++) {
			unsigned int flags = eb->flags[i];
			struct i915_vma *vma = eb->vma[i];

			if (flags & EXEC_OBJECT_PINNED &&
			    flags & __EXEC_OBJECT_HAS_PIN)
				continue;

			eb_unreserve_vma(vma, &eb->flags[i]);

			if (flags & EXEC_OBJECT_PINNED)
				
				list_add(&vma->exec_link, &eb->unbound);
			else if (flags & __EXEC_OBJECT_NEEDS_MAP)
				
				list_add_tail(&vma->exec_link, &eb->unbound);
			else if (!(flags & EXEC_OBJECT_SUPPORTS_48B_ADDRESS))
				
				list_add(&vma->exec_link, &last);
			else
				list_add_tail(&vma->exec_link, &last);
		}
		list_splice_tail(&last, &eb->unbound);

		switch (pass++) {
		case 0:
			break;

		case 1:
			
			err = i915_gem_evict_vm(eb->vm);
			if (err)
				return err;
			break;

		default:
			return -ENOSPC;
		}
	} while (1);
}