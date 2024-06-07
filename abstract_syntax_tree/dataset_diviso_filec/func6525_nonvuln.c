ins_ctrl_x(void)
{
    if (!ctrl_x_mode_cmdline())
    {
	
	if (compl_cont_status & CONT_N_ADDS)
	    compl_cont_status |= CONT_INTRPT;
	else
	    compl_cont_status = 0;
	
	ctrl_x_mode = CTRL_X_NOT_DEFINED_YET;
	edit_submode = (char_u *)_(CTRL_X_MSG(ctrl_x_mode));
	edit_submode_pre = NULL;
	showmode();
    }
    else
	
	
	ctrl_x_mode = CTRL_X_CMDLINE_CTRL_X;

    may_trigger_modechanged();
}