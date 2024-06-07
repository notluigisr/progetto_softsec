xmlXPtrNewContext(xmlDocPtr doc, xmlNodePtr here, xmlNodePtr origin) {
    xmlXPathContextPtr ret;

    ret = xmlXPathNewContext(doc);
    if (ret == NULL)
	return(ret);
    ret->xptr = 1;
    ret->here = here;
    ret->origin = origin;

    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrRangeToFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrRangeFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrRangeInsideFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrStringRangeFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrStartPointFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrEndPointFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrHereFunction);
    xmlXPathRegisterFunc(ret, (xmlChar *)"STR",
	                 xmlXPtrOriginFunction);

    return(ret);
}