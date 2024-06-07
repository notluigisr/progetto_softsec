pixWriteMemTiffCustom(l_uint8  **pdata,
                      size_t    *psize,
                      PIX       *pix,
                      l_int32    comptype,
                      NUMA      *natags,
                      SARRAY    *savals,
                      SARRAY    *satypes,
                      NUMA      *nasizes)
{
l_int32  ret;
TIFF    *tif;

    PROCNAME("STR");

    if (!pdata)
        return ERROR_INT("STR", procName, 1);
    if (!psize)
        return ERROR_INT("STR", procName, 1);
    if (!pix)
        return ERROR_INT("STR", procName, 1);
    if (pixGetDepth(pix) != 1 && comptype != IFF_TIFF &&
        comptype != IFF_TIFF_LZW && comptype != IFF_TIFF_ZIP &&
        comptype != IFF_TIFF_JPEG) {
        L_WARNING("STR", procName);
        comptype = IFF_TIFF_ZIP;
    }

    if ((tif = fopenTiffMemstream("STR", pdata, psize)) == NULL)
        return ERROR_INT("STR", procName, 1);
    ret = pixWriteToTiffStream(tif, pix, comptype, natags, savals,
                               satypes, nasizes);

    TIFFClose(tif);
    return ret;
}