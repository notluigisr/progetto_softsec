htmlParsePubidLiteral(htmlParserCtxtPtr ctxt) {
    const xmlChar *q;
    xmlChar *ret = NULL;
    
    if (CUR == '"') {
        NEXT;
	q = CUR_PTR;
	while (IS_PUBIDCHAR_CH(CUR)) NEXT;
	if (CUR != '"') {
	    htmlParseErr(ctxt, XML_ERR_LITERAL_NOT_FINISHED,
	                 "STR", NULL, NULL);
	} else {
	    ret = xmlStrndup(q, CUR_PTR - q);
	    NEXT;
	}
    } else if (CUR == '\'') {
        NEXT;
	q = CUR_PTR;
	while ((IS_PUBIDCHAR_CH(CUR)) && (CUR != '\''))
	    NEXT;
	if (CUR != '\'') {
	    htmlParseErr(ctxt, XML_ERR_LITERAL_NOT_FINISHED,
	                 "STR", NULL, NULL);
	} else {
	    ret = xmlStrndup(q, CUR_PTR - q);
	    NEXT;
	}
    } else {
	htmlParseErr(ctxt, XML_ERR_LITERAL_NOT_STARTED,
	             "STR", NULL, NULL);
    }

    return(ret);
}