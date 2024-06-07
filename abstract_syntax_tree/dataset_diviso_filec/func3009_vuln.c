gplotAddPlot(GPLOT       *gplot,
             NUMA        *nax,
             NUMA        *nay,
             l_int32      plotstyle,
             const char  *plottitle)
{
char       buf[L_BUF_SIZE];
char       emptystring[] = "";
char      *datastr, *title;
l_int32    n, i;
l_float32  valx, valy, startx, delx;
SARRAY    *sa;

    PROCNAME("STR");

    if (!gplot)
        return ERROR_INT("STR", procName, 1);
    if (!nay)
        return ERROR_INT("STR", procName, 1);
    if (plotstyle < 0 || plotstyle >= NUM_GPLOT_STYLES)
        return ERROR_INT("STR", procName, 1);

    if ((n = numaGetCount(nay)) == 0)
        return ERROR_INT("STR", procName, 1);
    if (nax && (n != numaGetCount(nax)))
        return ERROR_INT("STR", procName, 1);
    if (n == 1 && plotstyle == GPLOT_LINES) {
        L_INFO("STR", procName);
        plotstyle = GPLOT_POINTS;
    }

        
    numaGetParameters(nay, &startx, &delx);
    numaAddNumber(gplot->plotstyles, plotstyle);
    if (plottitle) {
        title = stringNew(plottitle);
        sarrayAddString(gplot->plottitles, title, L_INSERT);
    } else {
        sarrayAddString(gplot->plottitles, emptystring, L_COPY);
    }

        
    gplot->nplots++;
    snprintf(buf, L_BUF_SIZE, "STR", gplot->rootname, gplot->nplots);
    sarrayAddString(gplot->datanames, buf, L_COPY);

        
    sa = sarrayCreate(n);
    for (i = 0; i < n; i++) {
        if (nax)
            numaGetFValue(nax, i, &valx);
        else
            valx = startx + i * delx;
        numaGetFValue(nay, i, &valy);
        snprintf(buf, L_BUF_SIZE, "STR", valx, valy);
        sarrayAddString(sa, buf, L_COPY);
    }
    datastr = sarrayToString(sa, 0);
    sarrayAddString(gplot->plotdata, datastr, L_INSERT);
    sarrayDestroy(&sa);

    return 0;
}