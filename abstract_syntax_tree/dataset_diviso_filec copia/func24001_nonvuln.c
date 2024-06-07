make_optional_header_string(char *s)
{
    char *p;
    Str hs;

    if (strchr(s, '\n') || strchr(s, '\r'))
	return NULL;
    for (p = s; *p && *p != ':'; p++) ;
    if (*p != ':' || p == s)
	return NULL;
    hs = Strnew_size(strlen(s) + 3);
    Strcopy_charp_n(hs, s, p - s);
    if (!Strcasecmp_charp(hs, "STR"))
	override_content_type = TRUE;
    Strcat_charp(hs, "STR");
    if (*(++p)) {		
	SKIP_BLANKS(p);		
	Strcat_charp(hs, p);
    }
    Strcat_charp(hs, "STR");
    return hs;
}