alt_tabpage(void)
{
    tabpage_T	*tp;

    
    if (curtab->tp_next != NULL)
	return curtab->tp_next;

    
    for (tp = first_tabpage; tp->tp_next != curtab; tp = tp->tp_next)
	;
    return tp;
}