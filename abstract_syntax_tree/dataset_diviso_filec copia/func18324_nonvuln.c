int propfind_collectionname(const xmlChar *name, xmlNsPtr ns,
                            struct propfind_ctx *fctx,
                            xmlNodePtr prop, xmlNodePtr resp,
                            struct propstat propstat[], void *rock)
{
    int r = propfind_fromdb(name, ns, fctx, prop, resp, propstat, rock);

    if (r && fctx->mbentry && !fctx->req_tgt->resource) {
        
        xmlNodePtr node = xml_add_prop(HTTP_OK, fctx->ns[NS_DAV],
                                       &propstat[PROPSTAT_OK], name, ns, NULL, 0);
        buf_setcstr(&fctx->buf, strrchr(fctx->mbentry->name, '.') + 1);
        xmlAddChild(node, xmlNewCDataBlock(fctx->root->doc,
                                           BAD_CAST buf_cstring(&fctx->buf),
                                           buf_len(&fctx->buf)));
        return 0;
    }

    return r;
}