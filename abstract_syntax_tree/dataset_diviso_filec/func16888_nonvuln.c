ex_undo(exarg_T *eap)
{
    if (eap->addr_count == 1)	    
	undo_time(eap->line2, FALSE, FALSE, TRUE);
    else
	u_undo(1);
}