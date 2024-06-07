xmlSchemaPInternalErr(xmlSchemaParserCtxtPtr pctxt,
		     const char *funcName,
		     const char *message,
		     const xmlChar *str1,
		     const xmlChar *str2)
{
    xmlSchemaInternalErr2(ACTXT_CAST pctxt, funcName, message,
	str1, str2);
}