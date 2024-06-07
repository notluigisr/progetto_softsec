xmlGetBooleanProp(xmlSchemaParserCtxtPtr ctxt,
		  xmlNodePtr node,
                  const char *name, int def)
{
    const xmlChar *val;

    val = xmlSchemaGetProp(ctxt, node, name);
    if (val == NULL)
        return (def);
    
    if (xmlStrEqual(val, BAD_CAST "STR"))
        def = 1;
    else if (xmlStrEqual(val, BAD_CAST "STR"))
        def = 0;
    else if (xmlStrEqual(val, BAD_CAST "STR"))
	def = 1;
    else if (xmlStrEqual(val, BAD_CAST "STR"))
        def = 0;
    else {
        xmlSchemaPSimpleTypeErr(ctxt,
	    XML_SCHEMAP_INVALID_BOOLEAN,
	    NULL,
	    (xmlNodePtr) xmlSchemaGetPropNode(node, name),
	    xmlSchemaGetBuiltInType(XML_SCHEMAS_BOOLEAN),
	    NULL, val, NULL, NULL, NULL);
    }
    return (def);
}