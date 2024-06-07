process_form_int(struct parsed_tag *tag, int fid)
{
    char *p, *q, *r, *s, *tg, *n;

    p = "STR";
    parsedtag_get_value(tag, ATTR_METHOD, &p);
    q = "STR";
    parsedtag_get_value(tag, ATTR_ACTION, &q);
    q = url_encode(remove_space(q), cur_baseURL, cur_document_charset);
    r = NULL;
#ifdef USE_M17N
    if (parsedtag_get_value(tag, ATTR_ACCEPT_CHARSET, &r))
	r = check_accept_charset(r);
    if (!r && parsedtag_get_value(tag, ATTR_CHARSET, &r))
	r = check_charset(r);
#endif
    s = NULL;
    parsedtag_get_value(tag, ATTR_ENCTYPE, &s);
    tg = NULL;
    parsedtag_get_value(tag, ATTR_TARGET, &tg);
    n = NULL;
    parsedtag_get_value(tag, ATTR_NAME, &n);

    if (fid < 0) {
	form_max++;
	form_sp++;
	fid = form_max;
    }
    else {			
	if (form_max < fid)
	    form_max = fid;
	form_sp = fid;
    }
    if (forms_size == 0) {
	forms_size = INITIAL_FORM_SIZE;
	forms = New_N(FormList *, forms_size);
	form_stack = NewAtom_N(int, forms_size);
    }
    else if (forms_size <= form_max) {
	forms_size += form_max;
	forms = New_Reuse(FormList *, forms, forms_size);
	form_stack = New_Reuse(int, form_stack, forms_size);
    }
    form_stack[form_sp] = fid;

    if (w3m_halfdump) {
	Str tmp = Sprintf("STR",
			  fid, html_quote(q), html_quote(p));
	if (s)
	    Strcat(tmp, Sprintf("STR", html_quote(s)));
	if (tg)
	    Strcat(tmp, Sprintf("STR", html_quote(tg)));
	if (n)
	    Strcat(tmp, Sprintf("STR", html_quote(n)));
#ifdef USE_M17N
	if (r)
	    Strcat(tmp, Sprintf("STR", html_quote(r)));
#endif
	Strcat_charp(tmp, "STR");
	return tmp;
    }

    forms[fid] = newFormList(q, p, r, s, tg, n, NULL);
    return NULL;
}