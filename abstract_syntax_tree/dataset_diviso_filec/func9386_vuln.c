spop(void)
{
    static char dummy[] = "";	
    char *result = dummy;
    if (TPS(stack_ptr) > 0) {
	TPS(stack_ptr)--;
	if (!TPS(stack)[TPS(stack_ptr)].num_type
	    && TPS(stack)[TPS(stack_ptr)].data.str != 0)
	    result = TPS(stack)[TPS(stack_ptr)].data.str;
    } else {
	DEBUG(2, ("STR", _nc_visbuf(TPS(tparam_base))));
	_nc_tparm_err++;
    }
    return result;
}