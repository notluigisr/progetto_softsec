xmlSchemaAddNotation(xmlSchemaParserCtxtPtr ctxt, xmlSchemaPtr schema,
                     const xmlChar *name, const xmlChar *nsName,
		     xmlNodePtr node ATTRIBUTE_UNUSED)
{
    xmlSchemaNotationPtr ret = NULL;

    if ((ctxt == NULL) || (schema == NULL) || (name == NULL))
        return (NULL);

    ret = (xmlSchemaNotationPtr) xmlMalloc(sizeof(xmlSchemaNotation));
    if (ret == NULL) {
        xmlSchemaPErrMemory(ctxt, "STR", NULL);
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlSchemaNotation));
    ret->type = XML_SCHEMA_TYPE_NOTATION;
    ret->name = name;
    ret->targetNamespace = nsName;
    
    WXS_ADD_GLOBAL(ctxt, ret);
    return (ret);
}