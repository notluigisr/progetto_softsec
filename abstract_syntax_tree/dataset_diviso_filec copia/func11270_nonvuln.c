nv_ctrlg(cmdarg_T *cap)
{
    if (VIsual_active)	
    {
	VIsual_select = !VIsual_select;
	may_trigger_modechanged();
	showmode();
    }
    else if (!checkclearop(cap->oap))
	
	fileinfo((int)cap->count0, FALSE, TRUE);
}