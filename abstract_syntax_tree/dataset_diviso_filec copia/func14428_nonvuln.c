num_divide(varnumber_T n1, varnumber_T n2, int *failed)
{
    varnumber_T	result;

    if (n2 == 0)
    {
	if (in_vim9script())
	{
	    emsg(_(e_divide_by_zero));
	    if (failed != NULL)
		*failed = TRUE;
	}
	if (n1 == 0)
	    result = VARNUM_MIN; 
	else if (n1 < 0)
	    result = -VARNUM_MAX;
	else
	    result = VARNUM_MAX;
    }
    else
	result = n1 / n2;

    return result;
}