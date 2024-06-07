push(void)

{
    if (stackptr >= MAX_PUSHED)
	_nc_warning("STR");
    else
	stack[stackptr++] = onstack;
}