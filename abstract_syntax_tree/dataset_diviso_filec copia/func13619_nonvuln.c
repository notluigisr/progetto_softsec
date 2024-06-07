xmlSchemaDebugFixedType(xmlSchemaParserCtxtPtr pctxt,
		       xmlSchemaTypePtr type)
{
    if (type->node != NULL) {
        xmlGenericError(xmlGenericErrorContext,
                        "STR", name,
                        type->node->doc->URL,
                        xmlGetLineNo(type->node));
    } else {
        xmlGenericError(xmlGenericErrorContext, "STR", name);
    }
    if ((WXS_IS_SIMPLE(type)) || (WXS_IS_COMPLEX(type))) {
	switch (type->contentType) {
	    case XML_SCHEMA_CONTENT_SIMPLE:
		xmlGenericError(xmlGenericErrorContext, "STR");
		break;
	    case XML_SCHEMA_CONTENT_ELEMENTS:
		xmlGenericError(xmlGenericErrorContext, "STR");
		break;
	    case XML_SCHEMA_CONTENT_UNKNOWN:
		xmlGenericError(xmlGenericErrorContext, "STR");
		break;
	    case XML_SCHEMA_CONTENT_EMPTY:
		xmlGenericError(xmlGenericErrorContext, "STR");
		break;
	    case XML_SCHEMA_CONTENT_MIXED:
		if (xmlSchemaIsParticleEmptiable((xmlSchemaParticlePtr)
		    type->subtypes))
		    xmlGenericError(xmlGenericErrorContext,
			"STR");
		else
		    xmlGenericError(xmlGenericErrorContext, "STR");
		break;
		
		
	    case XML_SCHEMA_CONTENT_BASIC:
		xmlGenericError(xmlGenericErrorContext, "STR");
		break;
	    default:
		xmlGenericError(xmlGenericErrorContext,
		    "STR");
		break;
	}
    }
}