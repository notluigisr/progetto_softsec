ptaaInitFull(PTAA  *ptaa,
             PTA   *pta)
{
l_int32  n, i;
PTA     *ptat;

    PROCNAME("STR");

    if (!ptaa)
        return ERROR_INT("STR", procName, 1);
    if (!pta)
        return ERROR_INT("STR", procName, 1);

    n = ptaa->nalloc;
    ptaa->n = n;
    for (i = 0; i < n; i++) {
        ptat = ptaCopy(pta);
        ptaaReplacePta(ptaa, i, ptat);
    }
    return 0;
}