ignorableWhitespaceSplit(void *ctx, const xmlChar *ch, int len)
{
    xmlSchemaSAXPlugPtr ctxt = (xmlSchemaSAXPlugPtr) ctx;
    if (ctxt == NULL)
        return;
    if ((ctxt->user_sax != NULL) &&
        (ctxt->user_sax->ignorableWhitespace != NULL))
	ctxt->user_sax->ignorableWhitespace(ctxt->user_data, ch, len);
    if (ctxt->ctxt != NULL)
	xmlSchemaSAXHandleText(ctxt->ctxt, ch, len);
}