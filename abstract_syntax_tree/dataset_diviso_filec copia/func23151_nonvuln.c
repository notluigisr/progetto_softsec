has_state_with_pos(
    nfa_list_T		*l,	
    nfa_state_T		*state,	
    regsubs_T		*subs,	
    nfa_pim_T		*pim)	
{
    nfa_thread_T	*thread;
    int			i;

    for (i = 0; i < l->n; ++i)
    {
	thread = &l->t[i];
	if (thread->state->id == state->id
		&& sub_equal(&thread->subs.norm, &subs->norm)
#ifdef FEAT_SYN_HL
		&& (!rex.nfa_has_zsubexpr
				|| sub_equal(&thread->subs.synt, &subs->synt))
#endif
		&& pim_equal(&thread->pim, pim))
	    return TRUE;
    }
    return FALSE;
}