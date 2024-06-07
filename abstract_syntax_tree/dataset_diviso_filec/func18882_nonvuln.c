xmlSchemaTypeFixupWhitespace(xmlSchemaTypePtr type)
{


    
    if (WXS_IS_LIST(type)) {
	type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_COLLAPSE;
	return (0);
    } else if (WXS_IS_UNION(type))
	return (0);

    if (type->facetSet != NULL) {
	xmlSchemaFacetLinkPtr lin;

	for (lin = type->facetSet; lin != NULL; lin = lin->next) {
	    if (lin->facet->type == XML_SCHEMA_FACET_WHITESPACE) {
		switch (lin->facet->whitespace) {
		case XML_SCHEMAS_FACET_PRESERVE:
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_PRESERVE;
		    break;
		case XML_SCHEMAS_FACET_REPLACE:
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_REPLACE;
		    break;
		case XML_SCHEMAS_FACET_COLLAPSE:
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_COLLAPSE;
		    break;
		default:
		    return (-1);
		}
		return (0);
	    }
	}
    }
    
    {
	xmlSchemaTypePtr anc;

	for (anc = type->baseType; anc != NULL &&
		anc->builtInType != XML_SCHEMAS_ANYTYPE;
		anc = anc->baseType) {

	    if (anc->type == XML_SCHEMA_TYPE_BASIC) {
		if (anc->builtInType == XML_SCHEMAS_NORMSTRING) {
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_REPLACE;

		} else if ((anc->builtInType == XML_SCHEMAS_STRING) ||
		    (anc->builtInType == XML_SCHEMAS_ANYSIMPLETYPE)) {
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_PRESERVE;

		} else
		    type->flags |= XML_SCHEMAS_TYPE_WHITESPACE_COLLAPSE;
		break;
	    }
	}
    }
    return (0);
}