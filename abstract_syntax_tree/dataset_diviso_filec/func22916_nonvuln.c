matching_line_len(char_u *lbuf)
{
    char_u	*p = lbuf + 1;

    
    p += STRLEN(p) + 1;
#ifdef FEAT_EMACS_TAGS
    p += STRLEN(p) + 1;
#endif
    return (p - lbuf) + STRLEN(p);
}