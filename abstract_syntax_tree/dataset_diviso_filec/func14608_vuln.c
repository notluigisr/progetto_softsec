openscript(
    char_u	*name,
    int		directly)	
{
    if (curscript + 1 == NSCRIPT)
    {
	emsg(_(e_nesting));
	return;
    }
#ifdef FEAT_EVAL
    if (ignore_script)
	
	return;
#endif

    if (scriptin[curscript] != NULL)	
	++curscript;
				
    expand_env(name, NameBuff, MAXPATHL);
    if ((scriptin[curscript] = mch_fopen((char *)NameBuff, READBIN)) == NULL)
    {
	semsg(_(e_notopen), name);
	if (curscript)
	    --curscript;
	return;
    }
    if (save_typebuf() == FAIL)
	return;

    
    if (directly)
    {
	oparg_T	oa;
	int	oldcurscript;
	int	save_State = State;
	int	save_restart_edit = restart_edit;
	int	save_insertmode = p_im;
	int	save_finish_op = finish_op;
	int	save_msg_scroll = msg_scroll;

	State = NORMAL;
	msg_scroll = FALSE;	
	restart_edit = 0;	
	p_im = FALSE;		
	clear_oparg(&oa);
	finish_op = FALSE;

	oldcurscript = curscript;
	do
	{
	    update_topline_cursor();	
	    normal_cmd(&oa, FALSE);	
	    vpeekc();			
	}
	while (scriptin[oldcurscript] != NULL);

	State = save_State;
	msg_scroll = save_msg_scroll;
	restart_edit = save_restart_edit;
	p_im = save_insertmode;
	finish_op = save_finish_op;
    }
}