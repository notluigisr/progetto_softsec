replace_pop(void)
{
    if (replace_stack_nr == 0)
	return -1;
    return (int)replace_stack[--replace_stack_nr];
}