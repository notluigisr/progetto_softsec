xmlTextReaderSetSchema(xmlTextReaderPtr reader, xmlSchemaPtr schema) {
    if (reader == NULL)
        return(-1);
    if (schema == NULL) {
	if (reader->xsdPlug != NULL) {
	    xmlSchemaSAXUnplug(reader->xsdPlug);
	    reader->xsdPlug = NULL;
	}
        if (reader->xsdValidCtxt != NULL) {
	    if (! reader->xsdPreserveCtxt)
		xmlSchemaFreeValidCtxt(reader->xsdValidCtxt);
	    reader->xsdValidCtxt = NULL;
        }
	reader->xsdPreserveCtxt = 0;
        if (reader->xsdSchemas != NULL) {
	    xmlSchemaFree(reader->xsdSchemas);
	    reader->xsdSchemas = NULL;
	}
	return(0);
    }
    if (reader->mode != XML_TEXTREADER_MODE_INITIAL)
	return(-1);
    if (reader->xsdPlug != NULL) {
	xmlSchemaSAXUnplug(reader->xsdPlug);
	reader->xsdPlug = NULL;
    }
    if (reader->xsdValidCtxt != NULL) {
	if (! reader->xsdPreserveCtxt)
	    xmlSchemaFreeValidCtxt(reader->xsdValidCtxt);
	reader->xsdValidCtxt = NULL;
    }
    reader->xsdPreserveCtxt = 0;
    if (reader->xsdSchemas != NULL) {
	xmlSchemaFree(reader->xsdSchemas);
	reader->xsdSchemas = NULL;
    }
    reader->xsdValidCtxt = xmlSchemaNewValidCtxt(schema);
    if (reader->xsdValidCtxt == NULL) {
	xmlSchemaFree(reader->xsdSchemas);
	reader->xsdSchemas = NULL;
        return(-1);
    }
    reader->xsdPlug = xmlSchemaSAXPlug(reader->xsdValidCtxt,
                                       &(reader->ctxt->sax),
				       &(reader->ctxt->userData));
    if (reader->xsdPlug == NULL) {
	xmlSchemaFree(reader->xsdSchemas);
	reader->xsdSchemas = NULL;
	xmlSchemaFreeValidCtxt(reader->xsdValidCtxt);
	reader->xsdValidCtxt = NULL;
	return(-1);
    }
    xmlSchemaValidateSetLocator(reader->xsdValidCtxt,
                                xmlTextReaderLocator,
				(void *) reader);

    if (reader->errorFunc != NULL) {
	xmlSchemaSetValidErrors(reader->xsdValidCtxt,
			xmlTextReaderValidityErrorRelay,
			xmlTextReaderValidityWarningRelay,
			reader);
    }
	if (reader->sErrorFunc != NULL) {
		xmlSchemaSetValidStructuredErrors(reader->xsdValidCtxt,
			xmlTextReaderValidityStructuredRelay,
			reader);
    }
    reader->xsdValidErrors = 0;
    reader->validate = XML_TEXTREADER_VALIDATE_XSD;
    return(0);
}