xmlSchemaSimpleTypeErr(xmlSchemaAbstractCtxtPtr actxt,
		       xmlParserErrors error,
		       xmlNodePtr node,
		       const xmlChar *value,
		       xmlSchemaTypePtr type,
		       int displayValue)
{
    xmlChar *msg = NULL;

    xmlSchemaFormatNodeForError(&msg, actxt, node);

    if (displayValue || (xmlSchemaEvalErrorNodeType(actxt, node) ==
	    XML_ATTRIBUTE_NODE))
	msg = xmlStrcat(msg, BAD_CAST "STR");
    else
	msg = xmlStrcat(msg, BAD_CAST "STR"
	    "STR");

    if (! xmlSchemaIsGlobalItem(type))
	msg = xmlStrcat(msg, BAD_CAST "STR");
    else
	msg = xmlStrcat(msg, BAD_CAST "STR");

    if (WXS_IS_ATOMIC(type))
	msg = xmlStrcat(msg, BAD_CAST "STR");
    else if (WXS_IS_LIST(type))
	msg = xmlStrcat(msg, BAD_CAST "STR");
    else if (WXS_IS_UNION(type))
	msg = xmlStrcat(msg, BAD_CAST "STR");

    if (xmlSchemaIsGlobalItem(type)) {
	xmlChar *str = NULL;
	msg = xmlStrcat(msg, BAD_CAST "STR");
	if (type->builtInType != 0) {
	    msg = xmlStrcat(msg, BAD_CAST "STR");
	    msg = xmlStrcat(msg, type->name);
	} else
	    msg = xmlStrcat(msg,
		xmlSchemaFormatQName(&str,
		    type->targetNamespace, type->name));
	msg = xmlStrcat(msg, BAD_CAST "STR");
	FREE_AND_NULL(str);
    }
    msg = xmlStrcat(msg, BAD_CAST "STR");
    if (displayValue || (xmlSchemaEvalErrorNodeType(actxt, node) ==
	    XML_ATTRIBUTE_NODE))
	xmlSchemaErr(actxt, error, node, (const char *) msg, value, NULL);
    else
	xmlSchemaErr(actxt, error, node, (const char *) msg, NULL, NULL);
    FREE_AND_NULL(msg)
}