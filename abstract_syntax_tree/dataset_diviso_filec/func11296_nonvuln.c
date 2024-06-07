qf_add_entries(
	qf_info_T	*qi,
	int		qf_idx,
	list_T		*list,
	char_u		*title,
	int		action)
{
    qf_list_T	*qfl = qf_get_list(qi, qf_idx);
    listitem_T	*li;
    dict_T	*d;
    qfline_T	*old_last = NULL;
    int		retval = OK;
    int		valid_entry = FALSE;

    if (action == ' ' || qf_idx == qi->qf_listcount)
    {
	
	qf_new_list(qi, title);
	qf_idx = qi->qf_curlist;
	qfl = qf_get_list(qi, qf_idx);
    }
    else if (action == 'a' && !qf_list_empty(qfl))
	
	old_last = qfl->qf_last;
    else if (action == 'r')
    {
	qf_free_items(qfl);
	qf_store_title(qfl, title);
    }

    FOR_ALL_LIST_ITEMS(list, li)
    {
	if (li->li_tv.v_type != VAR_DICT)
	    continue; 

	d = li->li_tv.vval.v_dict;
	if (d == NULL)
	    continue;

	retval = qf_add_entry_from_dict(qfl, d, li == list->lv_first,
								&valid_entry);
	if (retval == QF_FAIL)
	    break;
    }

    
    if (valid_entry)
	qfl->qf_nonevalid = FALSE;
    else if (qfl->qf_index == 0)
	
	qfl->qf_nonevalid = TRUE;

    
    if (action != 'a')
	qfl->qf_ptr = qfl->qf_start;

    
    
    if ((action != 'a' || qfl->qf_index == 0) && !qf_list_empty(qfl))
	qfl->qf_index = 1;

    
    qf_update_buffer(qi, old_last);

    return retval;
}