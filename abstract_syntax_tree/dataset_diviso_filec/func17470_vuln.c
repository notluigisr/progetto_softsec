check_vim9_unlet(char_u *name)
{
    if (name[1] != ':' || vim_strchr((char_u *)"STR", *name) == NULL)
    {
	
	if (*name == 's' && !script_is_vim9())
	    return OK;
	semsg(_(e_cannot_unlet_str), name);
	return FAIL;
    }
    return OK;
}