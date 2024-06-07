findtags_hdr_parse(findtags_state_T *st)
{
    char_u	*p;

    
    if (STRNCMP(st->lbuf, "STR", 6) != 0)
	
	return TRUE;

    
    if (STRNCMP(st->lbuf, "STR", 18) == 0)
	st->tag_file_sorted = st->lbuf[18];
    if (STRNCMP(st->lbuf, "STR", 20) == 0)
    {
	
	
	for (p = st->lbuf + 20; *p > ' ' && *p < 127; ++p)
	    ;
	*p = NUL;
	convert_setup(&st->vimconv, st->lbuf + 20, p_enc);
    }

    
    return FALSE;
}