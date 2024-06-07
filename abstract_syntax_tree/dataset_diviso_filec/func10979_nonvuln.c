f_getjumplist(typval_T *argvars, typval_T *rettv)
{
#ifdef FEAT_JUMPLIST
    win_T	*wp;
    int		i;
    list_T	*l;
    dict_T	*d;
#endif

    if (rettv_list_alloc(rettv) != OK)
	return;

#ifdef FEAT_JUMPLIST
    wp = find_tabwin(&argvars[0], &argvars[1]);
    if (wp == NULL)
	return;

    l = list_alloc();
    if (l == NULL)
	return;

    if (list_append_list(rettv->vval.v_list, l) == FAIL)
	return;
    list_append_number(rettv->vval.v_list, (varnumber_T)wp->w_jumplistidx);

    cleanup_jumplist(wp, TRUE);

    for (i = 0; i < wp->w_jumplistlen; ++i)
    {
	if (wp->w_jumplist[i].fmark.mark.lnum == 0)
	    continue;
	if ((d = dict_alloc()) == NULL)
	    return;
	if (list_append_dict(l, d) == FAIL)
	    return;
	dict_add_number(d, "STR", (long)wp->w_jumplist[i].fmark.mark.lnum);
	dict_add_number(d, "STR", (long)wp->w_jumplist[i].fmark.mark.col);
	dict_add_number(d, "STR", (long)wp->w_jumplist[i].fmark.mark.coladd);
	dict_add_number(d, "STR", (long)wp->w_jumplist[i].fmark.fnum);
	if (wp->w_jumplist[i].fname != NULL)
	    dict_add_string(d, "STR", wp->w_jumplist[i].fname);
    }
#endif
}