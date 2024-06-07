save_submit_formlist(FormItemList *src)
{
    FormList *list;
    FormList *srclist;
    FormItemList *srcitem;
    FormItemList *item;
    FormItemList *ret = NULL;
#ifdef MENU_SELECT
    FormSelectOptionItem *opt;
    FormSelectOptionItem *curopt;
    FormSelectOptionItem *srcopt;
#endif				

    if (src == NULL)
	return NULL;
    srclist = src->parent;
    list = New(FormList);
    list->method = srclist->method;
    list->action = Strdup(srclist->action);
#ifdef USE_M17N
    list->charset = srclist->charset;
#endif
    list->enctype = srclist->enctype;
    list->nitems = srclist->nitems;
    list->body = srclist->body;
    list->boundary = srclist->boundary;
    list->length = srclist->length;

    for (srcitem = srclist->item; srcitem; srcitem = srcitem->next) {
	item = New(FormItemList);
	item->type = srcitem->type;
	item->name = Strdup(srcitem->name);
	item->value = Strdup(srcitem->value);
	item->checked = srcitem->checked;
	item->accept = srcitem->accept;
	item->size = srcitem->size;
	item->rows = srcitem->rows;
	item->maxlength = srcitem->maxlength;
	item->readonly = srcitem->readonly;
#ifdef MENU_SELECT
	opt = curopt = NULL;
	for (srcopt = srcitem->select_option; srcopt; srcopt = srcopt->next) {
	    if (!srcopt->checked)
		continue;
	    opt = New(FormSelectOptionItem);
	    opt->value = Strdup(srcopt->value);
	    opt->label = Strdup(srcopt->label);
	    opt->checked = srcopt->checked;
	    if (item->select_option == NULL) {
		item->select_option = curopt = opt;
	    }
	    else {
		curopt->next = opt;
		curopt = curopt->next;
	    }
	}
	item->select_option = opt;
	if (srcitem->label)
	    item->label = Strdup(srcitem->label);
#endif				
	item->parent = list;
	item->next = NULL;

	if (list->lastitem == NULL) {
	    list->item = list->lastitem = item;
	}
	else {
	    list->lastitem->next = item;
	    list->lastitem = item;
	}

	if (srcitem == src)
	    ret = item;
    }

    return ret;
}