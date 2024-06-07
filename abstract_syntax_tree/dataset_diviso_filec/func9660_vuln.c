static struct wildmat *split_wildmats(char *str)
{
    const char *prefix;
    char pattern[MAX_MAILBOX_BUFFER] = "", *p, *c;
    struct wildmat *wild = NULL;
    int n = 0;

    if ((prefix = config_getstring(IMAPOPT_NEWSPREFIX)))
	snprintf(pattern, sizeof(pattern), "STR", prefix);
    p = pattern + strlen(pattern);

    
    do {
	if ((c = strrchr(str, ',')))
	    *c++ = '\0';
	else
	    c = str;

	if (!(n % 10)) 
	    wild = xrealloc(wild, (n + 11) * sizeof(struct wildmat));

	if (*c == '!') wild[n].not = 1;		
	else if (*c == '@') wild[n].not = -1;	
	else wild[n].not = 0;

	strcpy(p, wild[n].not ? c + 1 : c);
	wild[n++].pat = xstrdup(pattern);
    } while (c != str);
    wild[n].pat = NULL;

    return wild;
}