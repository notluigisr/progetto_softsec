set_option_sctx_idx(int opt_idx, int opt_flags, sctx_T script_ctx)
{
    int		both = (opt_flags & (OPT_LOCAL | OPT_GLOBAL)) == 0;
    int		indir = (int)options[opt_idx].indir;
    sctx_T	new_script_ctx = script_ctx;

    
    if (!(opt_flags & OPT_MODELINE))
	new_script_ctx.sc_lnum += SOURCING_LNUM;

    
    
    if (both || (opt_flags & OPT_GLOBAL) || (indir & (PV_BUF|PV_WIN)) == 0)
	options[opt_idx].script_ctx = new_script_ctx;
    if (both || (opt_flags & OPT_LOCAL))
    {
	if (indir & PV_BUF)
	    curbuf->b_p_script_ctx[indir & PV_MASK] = new_script_ctx;
	else if (indir & PV_WIN)
	    curwin->w_p_script_ctx[indir & PV_MASK] = new_script_ctx;
    }
}