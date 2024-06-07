call_qftf_func(qf_list_T *qfl, int qf_winid, long start_idx, long end_idx)
{
    callback_T	*cb = &qftf_cb;
    list_T	*qftf_list = NULL;

    
    
    
    if (qfl->qf_qftf_cb.cb_name != NULL)
	cb = &qfl->qf_qftf_cb;
    if (cb->cb_name != NULL)
    {
	typval_T	args[1];
	dict_T		*d;
	typval_T	rettv;

	
	if ((d = dict_alloc_lock(VAR_FIXED)) == NULL)
	    return NULL;
	dict_add_number(d, "STR", (long)IS_QF_LIST(qfl));
	dict_add_number(d, "STR", (long)qf_winid);
	dict_add_number(d, "STR", (long)qfl->qf_id);
	dict_add_number(d, "STR", start_idx);
	dict_add_number(d, "STR", end_idx);
	++d->dv_refcount;
	args[0].v_type = VAR_DICT;
	args[0].vval.v_dict = d;

	qftf_list = NULL;
	if (call_callback(cb, 0, &rettv, 1, args) != FAIL)
	{
	    if (rettv.v_type == VAR_LIST)
	    {
		qftf_list = rettv.vval.v_list;
		qftf_list->lv_refcount++;
	    }
	    clear_tv(&rettv);
	}
	dict_unref(d);
    }

    return qftf_list;
}