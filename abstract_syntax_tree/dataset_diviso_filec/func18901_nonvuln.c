ex_write(exarg_T *eap)
{
    if (eap->usefilter)		
	do_bang(1, eap, FALSE, TRUE, FALSE);
    else
	(void)do_write(eap);
}