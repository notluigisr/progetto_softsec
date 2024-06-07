xmlRelaxNGDumpValidError(xmlRelaxNGValidCtxtPtr ctxt)
{
    int i, j, k;
    xmlRelaxNGValidErrorPtr err, dup;

#ifdef DEBUG_ERROR
    xmlGenericError(xmlGenericErrorContext,
                    "STR", ctxt->errNr);
#endif
    for (i = 0, k = 0; i < ctxt->errNr; i++) {
        err = &ctxt->errTab[i];
        if (k < MAX_ERROR) {
            for (j = 0; j < i; j++) {
                dup = &ctxt->errTab[j];
                if ((err->err == dup->err) && (err->node == dup->node) &&
                    (xmlStrEqual(err->arg1, dup->arg1)) &&
                    (xmlStrEqual(err->arg2, dup->arg2))) {
                    goto skip;
                }
            }
            xmlRelaxNGShowValidError(ctxt, err->err, err->node, err->seq,
                                     err->arg1, err->arg2);
            k++;
        }
      skip:
        if (err->flags & ERROR_IS_DUP) {
            if (err->arg1 != NULL)
                xmlFree((xmlChar *) err->arg1);
            err->arg1 = NULL;
            if (err->arg2 != NULL)
                xmlFree((xmlChar *) err->arg2);
            err->arg2 = NULL;
            err->flags = 0;
        }
    }
    ctxt->errNr = 0;
}