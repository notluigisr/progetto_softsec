gplotCreate(const char  *rootname,
            l_int32      outformat,
            const char  *title,
            const char  *xlabel,
            const char  *ylabel)
{
char    *newroot;
char     buf[L_BUF_SIZE];
l_int32  badchar;
GPLOT   *gplot;

    PROCNAME("STR");

    if (!rootname)
        return (GPLOT *)ERROR_PTR("STR", procName, NULL);
    if (outformat != GPLOT_PNG && outformat != GPLOT_PS &&
        outformat != GPLOT_EPS && outformat != GPLOT_LATEX)
        return (GPLOT *)ERROR_PTR("STR", procName, NULL);
    stringCheckForChars(rootname, "STR", &badchar);
    if (badchar)  
        return (GPLOT *)ERROR_PTR("STR", procName, NULL);

    if ((gplot = (GPLOT *)LEPT_CALLOC(1, sizeof(GPLOT))) == NULL)
        return (GPLOT *)ERROR_PTR("STR", procName, NULL);
    gplot->cmddata = sarrayCreate(0);
    gplot->datanames = sarrayCreate(0);
    gplot->plotdata = sarrayCreate(0);
    gplot->plottitles = sarrayCreate(0);
    gplot->plotstyles = numaCreate(0);

        
    newroot = genPathname(rootname, NULL);
    gplot->rootname = newroot;
    gplot->outformat = outformat;
    snprintf(buf, L_BUF_SIZE, "STR", rootname);
    gplot->cmdname = stringNew(buf);
    if (outformat == GPLOT_PNG)
        snprintf(buf, L_BUF_SIZE, "STR", newroot);
    else if (outformat == GPLOT_PS)
        snprintf(buf, L_BUF_SIZE, "STR", newroot);
    else if (outformat == GPLOT_EPS)
        snprintf(buf, L_BUF_SIZE, "STR", newroot);
    else if (outformat == GPLOT_LATEX)
        snprintf(buf, L_BUF_SIZE, "STR", newroot);
    gplot->outname = stringNew(buf);
    if (title) gplot->title = stringNew(title);
    if (xlabel) gplot->xlabel = stringNew(xlabel);
    if (ylabel) gplot->ylabel = stringNew(ylabel);

    return gplot;
}