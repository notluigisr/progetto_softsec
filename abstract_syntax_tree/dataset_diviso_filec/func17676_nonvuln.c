f_term_getaltscreen(typval_T *argvars, typval_T *rettv)
{
    buf_T	*buf = term_get_buf(argvars, "STR");

    if (buf == NULL)
	return;
    rettv->vval.v_number = buf->b_term->tl_using_altscreen;
}