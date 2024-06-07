generate_loadvar(
	cctx_T		*cctx,
	assign_dest_T	dest,
	char_u		*name,
	lvar_T		*lvar,
	type_T		*type)
{
    switch (dest)
    {
	case dest_option:
	case dest_func_option:
	    generate_LOAD(cctx, ISN_LOADOPT, 0, name, type);
	    break;
	case dest_global:
	    if (vim_strchr(name, AUTOLOAD_CHAR) == NULL)
		generate_LOAD(cctx, ISN_LOADG, 0, name + 2, type);
	    else
		generate_LOAD(cctx, ISN_LOADAUTO, 0, name, type);
	    break;
	case dest_buffer:
	    generate_LOAD(cctx, ISN_LOADB, 0, name + 2, type);
	    break;
	case dest_window:
	    generate_LOAD(cctx, ISN_LOADW, 0, name + 2, type);
	    break;
	case dest_tab:
	    generate_LOAD(cctx, ISN_LOADT, 0, name + 2, type);
	    break;
	case dest_script:
	    compile_load_scriptvar(cctx,
		    name + (name[1] == ':' ? 2 : 0), NULL, NULL, TRUE);
	    break;
	case dest_env:
	    
	    generate_LOAD(cctx, ISN_LOADENV, 0, name, type);
	    break;
	case dest_reg:
	    generate_LOAD(cctx, ISN_LOADREG, name[1], NULL, &t_string);
	    break;
	case dest_vimvar:
	    generate_LOADV(cctx, name + 2, TRUE);
	    break;
	case dest_local:
	    if (lvar->lv_from_outer > 0)
		generate_LOADOUTER(cctx, lvar->lv_idx, lvar->lv_from_outer,
									 type);
	    else
		generate_LOAD(cctx, ISN_LOAD, lvar->lv_idx, NULL, type);
	    break;
	case dest_expr:
	    
	    break;
    }
}