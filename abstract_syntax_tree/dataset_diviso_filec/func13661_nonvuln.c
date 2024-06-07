get_list_line(
    int	    c UNUSED,
    void    *cookie,
    int	    indent UNUSED)
{
    listitem_T **p = (listitem_T **)cookie;
    listitem_T *item = *p;
    char_u	buf[NUMBUFLEN];
    char_u	*s;

    if (item == NULL)
	return NULL;
    s = tv_get_string_buf_chk(&item->li_tv, buf);
    *p = item->li_next;
    return s == NULL ? NULL : vim_strsave(s);
}