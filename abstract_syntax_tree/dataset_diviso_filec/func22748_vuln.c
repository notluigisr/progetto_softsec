pixBlockconvGray(PIX     *pixs,
                 PIX     *pixacc,
                 l_int32  wc,
                 l_int32  hc)
{
l_int32    w, h, d, wpl, wpla;
l_uint32  *datad, *dataa;
PIX       *pixd, *pixt;

    PROCNAME("STR");

    if (!pixs)
        return (PIX *)ERROR_PTR("STR", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8)
        return (PIX *)ERROR_PTR("STR", procName, NULL);
    if (wc < 0) wc = 0;
    if (hc < 0) hc = 0;
    if (w < 2 * wc + 1 || h < 2 * hc + 1) {
        wc = L_MIN(wc, (w - 1) / 2);
        hc = L_MIN(hc, (h - 1) / 2);
        L_WARNING("STR", procName);
        L_INFO("STR", procName, wc, hc);
    }
    if (wc == 0 && hc == 0)   
        return pixCopy(NULL, pixs);

    if (pixacc) {
        if (pixGetDepth(pixacc) == 32) {
            pixt = pixClone(pixacc);
        } else {
            L_WARNING("STR", procName);
            if ((pixt = pixBlockconvAccum(pixs)) == NULL)
                return (PIX *)ERROR_PTR("STR", procName, NULL);
        }
    } else {
        if ((pixt = pixBlockconvAccum(pixs)) == NULL)
            return (PIX *)ERROR_PTR("STR", procName, NULL);
    }

    if ((pixd = pixCreateTemplate(pixs)) == NULL) {
        pixDestroy(&pixt);
        return (PIX *)ERROR_PTR("STR", procName, NULL);
    }

    wpl = pixGetWpl(pixs);
    wpla = pixGetWpl(pixt);
    datad = pixGetData(pixd);
    dataa = pixGetData(pixt);
    blockconvLow(datad, w, h, wpl, dataa, wpla, wc, hc);

    pixDestroy(&pixt);
    return pixd;
}