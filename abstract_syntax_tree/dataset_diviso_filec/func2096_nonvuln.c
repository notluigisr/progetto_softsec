v_exception(char_u *oldval)
{
    if (oldval == NULL)
	return vimvars[VV_EXCEPTION].vv_str;

    vimvars[VV_EXCEPTION].vv_str = oldval;
    return NULL;
}