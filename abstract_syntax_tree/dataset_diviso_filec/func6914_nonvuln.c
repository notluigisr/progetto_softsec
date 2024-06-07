xmlRelaxNGSchemaFacetCheck(void *data ATTRIBUTE_UNUSED,
                           const xmlChar * type, const xmlChar * facetname,
                           const xmlChar * val, const xmlChar * strval,
                           void *value)
{
    xmlSchemaFacetPtr facet;
    xmlSchemaTypePtr typ;
    int ret;

    if ((type == NULL) || (strval == NULL))
        return (-1);
    typ = xmlSchemaGetPredefinedType(type,
                                     BAD_CAST
                                     "STR");
    if (typ == NULL)
        return (-1);

    facet = xmlSchemaNewFacet();
    if (facet == NULL)
        return (-1);

    if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MININCLUSIVE;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MINEXCLUSIVE;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MAXINCLUSIVE;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MAXEXCLUSIVE;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_TOTALDIGITS;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_FRACTIONDIGITS;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_PATTERN;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_ENUMERATION;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_WHITESPACE;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_LENGTH;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MAXLENGTH;
    } else if (xmlStrEqual(facetname, BAD_CAST "STR")) {
        facet->type = XML_SCHEMA_FACET_MINLENGTH;
    } else {
        xmlSchemaFreeFacet(facet);
        return (-1);
    }
    facet->value = val;
    ret = xmlSchemaCheckFacet(facet, typ, NULL, type);
    if (ret != 0) {
        xmlSchemaFreeFacet(facet);
        return (-1);
    }
    ret = xmlSchemaValidateFacet(typ, facet, strval, value);
    xmlSchemaFreeFacet(facet);
    if (ret != 0)
        return (-1);
    return (0);
}