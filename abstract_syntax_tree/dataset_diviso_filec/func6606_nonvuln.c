xmlSchemaFreeModelGroupDef(xmlSchemaModelGroupDefPtr item)
{
    if (item->annot != NULL)
	xmlSchemaFreeAnnot(item->annot);
    xmlFree(item);
}