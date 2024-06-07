xmlRelaxNGFreeDocument(xmlRelaxNGDocumentPtr docu)
{
    if (docu == NULL)
        return;

    if (docu->href != NULL)
        xmlFree(docu->href);
    if (docu->doc != NULL)
        xmlFreeDoc(docu->doc);
    if (docu->schema != NULL)
        xmlRelaxNGFreeInnerSchema(docu->schema);
    xmlFree(docu);
}