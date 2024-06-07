ex_doautoall(exarg_T *eap)
{
    int		retval = OK;
    aco_save_T	aco;
    buf_T	*buf;
    bufref_T	bufref;
    char_u	*arg = eap->arg;
    int		call_do_modelines = check_nomodeline(&arg);
    int		did_aucmd;

    
    FOR_ALL_BUFFERS(buf)
    {
	
	if (buf->b_ml.ml_mfp != NULL && buf != curbuf)
	{
	    
	    aucmd_prepbuf(&aco, buf);
	    set_bufref(&bufref, buf);

	    
	    retval = do_doautocmd(arg, FALSE, &did_aucmd);

	    if (call_do_modelines && did_aucmd)
		
		
		
		do_modelines(curwin == aucmd_win ? OPT_NOWIN : 0);

	    
	    aucmd_restbuf(&aco);

	    
	    if (retval == FAIL || !bufref_valid(&bufref))
	    {
		retval = FAIL;
		break;
	    }
	}
    }

    
    if (retval == OK)
    {
	do_doautocmd(arg, FALSE, &did_aucmd);
	if (call_do_modelines && did_aucmd)
	    do_modelines(0);
    }
}