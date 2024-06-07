ex_startinsert(exarg_T *eap)
{
    if (eap->forceit)
    {
	
	if (!curwin->w_cursor.lnum)
	    curwin->w_cursor.lnum = 1;
	coladvance((colnr_T)MAXCOL);
	curwin->w_curswant = MAXCOL;
	curwin->w_set_curswant = FALSE;
    }

    
    if (State & INSERT)
	return;

    if (eap->cmdidx == CMD_startinsert)
	restart_edit = 'a';
    else if (eap->cmdidx == CMD_startreplace)
	restart_edit = 'R';
    else
	restart_edit = 'V';

    if (!eap->forceit)
    {
	if (eap->cmdidx == CMD_startinsert)
	    restart_edit = 'i';
	curwin->w_curswant = 0;	    
    }
}