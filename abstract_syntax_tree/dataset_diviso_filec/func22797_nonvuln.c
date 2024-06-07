xmlSchemaPIllegalFacetAtomicErr(xmlSchemaParserCtxtPtr ctxt,
			  xmlParserErrors error,
			  xmlSchemaTypePtr type,
			  xmlSchemaTypePtr baseType,
			  xmlSchemaFacetPtr facet)
{
    xmlChar *des = NULL, *strT = NULL;

    xmlSchemaFormatItemForReport(&des, NULL, WXS_BASIC_CAST type, type->node);
    xmlSchemaPErrExt(ctxt, type->node, error, NULL, NULL, NULL,
	"STR"
	"STR",
	BAD_CAST des, xmlSchemaFacetTypeToString(facet->type),
	xmlSchemaFormatItemForReport(&strT, NULL, WXS_BASIC_CAST baseType, NULL),
	NULL, NULL);
    FREE_AND_NULL(des);
    FREE_AND_NULL(strT);
}