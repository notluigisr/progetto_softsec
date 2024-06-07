ex_endif(exarg_T *eap)
{
    cstack_T	*cstack = eap->cstack;

    if (cmdmod_error(FALSE))
	return;
    did_endif = TRUE;
    if (cstack->cs_idx < 0
	    || (cstack->cs_flags[cstack->cs_idx]
				& (CSF_WHILE | CSF_FOR | CSF_TRY | CSF_BLOCK)))
	eap->errmsg = _(e_endif_without_if);
    else
    {
	
	if (!(cstack->cs_flags[cstack->cs_idx] & CSF_TRUE)
						    && dbg_check_skipped(eap))
	    (void)do_intthrow(cstack);

	leave_block(cstack);
    }
}