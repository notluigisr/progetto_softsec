did_set_option(
    int	    opt_idx,
    int	    opt_flags,	    
    int	    new_value,	    
    int	    value_checked)  
			    
{
    long_u	*p;

    options[opt_idx].flags |= P_WAS_SET;

    
    
    
    p = insecure_flag(opt_idx, opt_flags);
    if (!value_checked && (secure
#ifdef HAVE_SANDBOX
	    || sandbox != 0
#endif
	    || (opt_flags & OPT_MODELINE)))
	*p = *p | P_INSECURE;
    else if (new_value)
	*p = *p & ~P_INSECURE;
}