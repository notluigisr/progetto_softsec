selReadStream(FILE  *fp)
{
char    *selname;
char     linebuf[L_BUF_SIZE];
l_int32  sy, sx, cy, cx, i, j, version, ignore;
SEL     *sel;

    PROCNAME("STR");

    if (!fp)
        return (SEL *)ERROR_PTR("STR", procName, NULL);

    if (fscanf(fp, "STR", &version) != 1)
        return (SEL *)ERROR_PTR("STR", procName, NULL);
    if (version != SEL_VERSION_NUMBER)
        return (SEL *)ERROR_PTR("STR", procName, NULL);

    if (fgets(linebuf, L_BUF_SIZE, fp) == NULL)
        return (SEL *)ERROR_PTR("STR", procName, NULL);
    selname = stringNew(linebuf);
    sscanf(linebuf, "STR", selname);

    if (fscanf(fp, "STR",
            &sy, &sx, &cy, &cx) != 4) {
        LEPT_FREE(selname);
        return (SEL *)ERROR_PTR("STR", procName, NULL);
    }

    if ((sel = selCreate(sy, sx, selname)) == NULL) {
        LEPT_FREE(selname);
        return (SEL *)ERROR_PTR("STR", procName, NULL);
    }
    selSetOrigin(sel, cy, cx);

    for (i = 0; i < sy; i++) {
        ignore = fscanf(fp, "STR");
        for (j = 0; j < sx; j++)
            ignore = fscanf(fp, "STR", &sel->data[i][j]);
        ignore = fscanf(fp, "STR");
    }
    ignore = fscanf(fp, "STR");

    LEPT_FREE(selname);
    return sel;
}