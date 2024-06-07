parsecolorchar(zattr arg, int is_fg)
{
    if (bv->fm[1] == '{') {
	char *ep;
	bv->fm += 2; 
	if ((ep = strchr(bv->fm, '}'))) {
	    char oc = *ep, *col, *coll;
	    *ep = '\0';
	    
	    coll = col = promptexpand(bv->fm, 0, NULL, NULL, NULL);
	    *ep = oc;
	    arg = match_colour((const char **)&coll, is_fg, 0);
	    free(col);
	    bv->fm = ep;
	} else {
	    arg = match_colour((const char **)&bv->fm, is_fg, 0);
	    if (*bv->fm != '}')
		bv->fm--;
	}
    } else
	arg = match_colour(NULL, 1, arg);
    return arg;
}