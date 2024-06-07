f_test_option_not_set(typval_T *argvars, typval_T *rettv UNUSED)
{
    char_u *name = (char_u *)"";

    if (argvars[0].v_type != VAR_STRING)
	emsg(_(e_invarg));
    else
    {
	name = tv_get_string(&argvars[0]);
	if (reset_option_was_set(name) == FAIL)
	    semsg(_(e_invarg2), name);
    }
}