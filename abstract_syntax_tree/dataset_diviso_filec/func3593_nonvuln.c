pixGetHoleBorder(CCBORD   *ccb,
                 PIX      *pixs,
                 BOX      *box,
                 l_int32   xs,
                 l_int32   ys)
{
l_int32    fpx, fpy, spx, spy, qpos;
l_int32    px, py, npx, npy;
l_int32    w, h, wpl;
l_uint32  *data;
PTA       *pta;

    PROCNAME("STR");

    if (!ccb)
        return ERROR_INT("STR", procName, 1);
    if (!pixs)
        return ERROR_INT("STR", procName, 1);
    if (!box)
        return ERROR_INT("STR", procName, 1);

        
    qpos = 0;   
    fpx = xs;  
    fpy = ys;

        
    boxaAddBox(ccb->boxa, box, L_COPY);
    ptaAddPt(ccb->start, xs, ys);

    pta = ptaCreate(0);
    ptaaAddPta(ccb->local, pta, L_INSERT);
    ptaAddPt(pta, xs, ys);   

    w = pixGetWidth(pixs);
    h = pixGetHeight(pixs);
    data = pixGetData(pixs);
    wpl = pixGetWpl(pixs);

        
    if (findNextBorderPixel(w, h, data, wpl, xs, ys, &qpos, &npx, &npy))
        return ERROR_INT("STR", procName, 1);

    spx = npx;  
    spy = npy;
    ptaAddPt(pta, npx, npy);   
    px = npx;
    py = npy;

    while (1) {
        findNextBorderPixel(w, h, data, wpl, px, py, &qpos, &npx, &npy);
        if (px == fpx && py == fpy && npx == spx && npy == spy)
            break;
        ptaAddPt(pta, npx, npy);
        px = npx;
        py = npy;
    }

    return 0;
}