getEntitySplit(void *ctx, const xmlChar *name)
{
    xmlSchemaSAXPlugPtr ctxt = (xmlSchemaSAXPlugPtr) ctx;
    if ((ctxt != NULL) && (ctxt->user_sax != NULL) &&
        (ctxt->user_sax->getEntity != NULL))
	return(ctxt->user_sax->getEntity(ctxt->user_data, name));
    return(NULL);
}