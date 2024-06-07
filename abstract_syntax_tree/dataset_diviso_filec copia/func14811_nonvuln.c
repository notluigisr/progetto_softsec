xmlSchemaCheckElementDeclComponent(xmlSchemaElementPtr elemDecl,
				   xmlSchemaParserCtxtPtr ctxt)
{
    if (elemDecl == NULL)
	return;
    if (elemDecl->flags & XML_SCHEMAS_ELEM_INTERNAL_CHECKED)
	return;
    elemDecl->flags |= XML_SCHEMAS_ELEM_INTERNAL_CHECKED;
    if (xmlSchemaCheckElemPropsCorrect(ctxt, elemDecl) == 0) {
	
	xmlSchemaCheckElemSubstGroup(ctxt, elemDecl);
    }
}