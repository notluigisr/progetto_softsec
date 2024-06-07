xmlSchemaFreeAttribute(xmlSchemaAttributePtr attr)
{
    if (attr == NULL)
        return;
    if (attr->annot != NULL)
	xmlSchemaFreeAnnot(attr->annot);
    if (attr->defVal != NULL)
	xmlSchemaFreeValue(attr->defVal);
    xmlFree(attr);
}