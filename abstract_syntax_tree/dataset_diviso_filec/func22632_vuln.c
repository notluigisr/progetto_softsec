htmlParseNameComplex(xmlParserCtxtPtr ctxt) {
    int len = 0, l;
    int c;
    int count = 0;

    
    GROW;
    c = CUR_CHAR(l);
    if ((c == ' ') || (c == '>') || (c == '/') || 
	(!IS_LETTER(c) && (c != '_') &&
         (c != ':'))) {
	return(NULL);
    }

    while ((c != ' ') && (c != '>') && (c != '/') && 
	   ((IS_LETTER(c)) || (IS_DIGIT(c)) ||
            (c == '.') || (c == '-') ||
	    (c == '_') || (c == ':') ||
	    (IS_COMBINING(c)) ||
	    (IS_EXTENDER(c)))) {
	if (count++ > 100) {
	    count = 0;
	    GROW;
	}
	len += l;
	NEXTL(l);
	c = CUR_CHAR(l);
    }
    return(xmlDictLookup(ctxt->dict, ctxt->input->cur - len, len));
}