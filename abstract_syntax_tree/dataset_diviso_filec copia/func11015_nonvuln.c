xmlRelaxNGFreeIncludeList(xmlRelaxNGIncludePtr incl)
{
    xmlRelaxNGIncludePtr next;

    while (incl != NULL) {
        next = incl->next;
        xmlRelaxNGFreeInclude(incl);
        incl = next;
    }
}