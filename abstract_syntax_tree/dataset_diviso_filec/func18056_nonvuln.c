int xt_check_entry_offsets(const void *base,
			   const char *elems,
			   unsigned int target_offset,
			   unsigned int next_offset)
{
	long size_of_base_struct = elems - (const char *)base;
	const struct xt_entry_target *t;
	const char *e = base;

	
	if (target_offset < size_of_base_struct)
		return -EINVAL;

	if (target_offset + sizeof(*t) > next_offset)
		return -EINVAL;

	t = (void *)(e + target_offset);
	if (t->u.target_size < sizeof(*t))
		return -EINVAL;

	if (target_offset + t->u.target_size > next_offset)
		return -EINVAL;

	if (strcmp(t->u.user.name, XT_STANDARD_TARGET) == 0 &&
	    target_offset + sizeof(struct xt_standard_target) != next_offset)
		return -EINVAL;

	return xt_check_entry_match(elems, base + target_offset,
				    __alignof__(struct xt_entry_match));
}