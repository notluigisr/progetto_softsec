xmlRelaxNGNewDocParserCtxt(xmlDocPtr doc)
{
    xmlRelaxNGParserCtxtPtr ret;
    xmlDocPtr copy;

    if (doc == NULL)
        return (NULL);
    copy = xmlCopyDoc(doc, 1);
    if (copy == NULL)
        return (NULL);

    ret =
        (xmlRelaxNGParserCtxtPtr) xmlMalloc(sizeof(xmlRelaxNGParserCtxt));
    if (ret == NULL) {
        xmlRngPErrMemory(NULL, "STR");
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlRelaxNGParserCtxt));
    ret->document = copy;
    ret->freedoc = 1;
    ret->userData = xmlGenericErrorContext;
    return (ret);
}