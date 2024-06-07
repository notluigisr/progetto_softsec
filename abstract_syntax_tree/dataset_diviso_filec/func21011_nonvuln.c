rewind_conditionals(
    cstack_T   *cstack,
    int		idx,
    int		cond_type,
    int		*cond_level)
{
    while (cstack->cs_idx > idx)
    {
	if (cstack->cs_flags[cstack->cs_idx] & cond_type)
	    --*cond_level;
	if (cstack->cs_flags[cstack->cs_idx] & CSF_FOR)
	    free_for_info(cstack->cs_forinfo[cstack->cs_idx]);
	leave_block(cstack);
    }
}