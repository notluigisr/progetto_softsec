compile_get_env(char_u **arg, cctx_T *cctx)
{
    char_u	*start = *arg;
    int		len;
    int		ret;
    char_u	*name;

    ++*arg;
    len = get_env_len(arg);
    if (len == 0)
    {
	semsg(_(e_syntax_error_at_str), start - 1);
	return FAIL;
    }

    
    name = vim_strnsave(start, len + 1);
    ret = generate_LOAD(cctx, ISN_LOADENV, 0, name, &t_string);
    vim_free(name);
    return ret;
}