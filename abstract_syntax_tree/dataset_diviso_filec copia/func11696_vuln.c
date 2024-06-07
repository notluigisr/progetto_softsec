selaGetCombName(SELA    *sela,
                l_int32  size,
                l_int32  direction)
{
char    *selname;
char     combname[L_BUF_SIZE];
l_int32  i, nsels, sx, sy, found;
SEL     *sel;

    PROCNAME("STR");

    if (!sela)
        return (char *)ERROR_PTR("STR", procName, NULL);
    if (direction != L_HORIZ && direction != L_VERT)
        return (char *)ERROR_PTR("STR", procName, NULL);

        
    if (direction == L_HORIZ)
        snprintf(combname, L_BUF_SIZE, "STR", size);
    else  
        snprintf(combname, L_BUF_SIZE, "STR", size);

    found = FALSE;
    nsels = selaGetCount(sela);
    for (i = 0; i < nsels; i++) {
        sel = selaGetSel(sela, i);
        selGetParameters(sel, &sy, &sx, NULL, NULL);
        if (sy != 1 && sx != 1)  
            continue;
        selname = selGetName(sel);
        if (!strcmp(selname, combname)) {
            found = TRUE;
            break;
        }
    }

    if (found)
        return stringNew(selname);
    else
        return (char *)ERROR_PTR("STR", procName, NULL);
}