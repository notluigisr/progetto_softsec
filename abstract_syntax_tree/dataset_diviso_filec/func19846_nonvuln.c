int propfind_getlength(const xmlChar *name, xmlNsPtr ns,
                       struct propfind_ctx *fctx,
                       xmlNodePtr prop __attribute__((unused)),
                       xmlNodePtr resp __attribute__((unused)),
                       struct propstat propstat[],
                       void *rock __attribute__((unused)))
{
    buf_reset(&fctx->buf);

    if (fctx->record) {
        buf_printf(&fctx->buf, "STR",
                   fctx->record->size - fctx->record->header_size);
    }

    xml_add_prop(HTTP_OK, fctx->ns[NS_DAV], &propstat[PROPSTAT_OK],
                 name, ns, BAD_CAST buf_cstring(&fctx->buf), 0);

    return 0;
}