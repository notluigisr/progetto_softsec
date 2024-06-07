ptaReadStream(FILE  *fp)
{
char       typestr[128];
l_int32    i, n, ix, iy, type, version;
l_float32  x, y;
PTA       *pta;

    PROCNAME("STR");

    if (!fp)
        return (PTA *)ERROR_PTR("STR", procName, NULL);

    if (fscanf(fp, "STR", &version) != 1)
        return (PTA *)ERROR_PTR("STR", procName, NULL);
    if (version != PTA_VERSION_NUMBER)
        return (PTA *)ERROR_PTR("STR", procName, NULL);
    if (fscanf(fp, "STR", &n, typestr) != 2)
        return (PTA *)ERROR_PTR("STR", procName, NULL);
    if (!strcmp(typestr, "STR"))
        type = 0;
    else  
        type = 1;

    if ((pta = ptaCreate(n)) == NULL)
        return (PTA *)ERROR_PTR("STR", procName, NULL);
    for (i = 0; i < n; i++) {
        if (type == 0) {  
            if (fscanf(fp, "STR", &x, &y) != 2) {
                ptaDestroy(&pta);
                return (PTA *)ERROR_PTR("STR", procName, NULL);
            }
            ptaAddPt(pta, x, y);
        } else {   
            if (fscanf(fp, "STR", &ix, &iy) != 2) {
                ptaDestroy(&pta);
                return (PTA *)ERROR_PTR("STR", procName, NULL);
            }
            ptaAddPt(pta, ix, iy);
        }
    }

    return pta;
}