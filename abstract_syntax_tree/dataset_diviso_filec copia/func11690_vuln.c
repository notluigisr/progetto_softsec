static struct binder_buffer *binder_alloc_prepare_to_free_locked(
		struct binder_alloc *alloc,
		uintptr_t user_ptr)
{
	struct rb_node *n = alloc->allocated_buffers.rb_node;
	struct binder_buffer *buffer;
	void *kern_ptr;

	kern_ptr = (void *)(user_ptr - alloc->user_buffer_offset);

	while (n) {
		buffer = rb_entry(n, struct binder_buffer, rb_node);
		BUG_ON(buffer->free);

		if (kern_ptr < buffer->data)
			n = n->rb_left;
		else if (kern_ptr > buffer->data)
			n = n->rb_right;
		else {
			
			if (buffer->free_in_progress) {
				binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
						   "STR",
						   alloc->pid, current->pid,
						   (u64)user_ptr);
				return NULL;
			}
			buffer->free_in_progress = 1;
			return buffer;
		}
	}
	return NULL;
}