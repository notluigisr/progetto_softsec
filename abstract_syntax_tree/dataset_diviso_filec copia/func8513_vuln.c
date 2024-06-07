static void do_under_overlay_for_page(
    QPDF& pdf,
    Options& o,
    UnderOverlay& uo,
    std::map<int, std::vector<int> >& pagenos,
    size_t page_idx,
    std::map<int, QPDFObjectHandle>& fo,
    std::vector<QPDFPageObjectHelper>& pages,
    QPDFPageObjectHelper& dest_page,
    bool before)
{
    int pageno = 1 + page_idx;
    if (! pagenos.count(pageno))
    {
        return;
    }

    std::string content;
    int min_suffix = 1;
    QPDFObjectHandle resources = dest_page.getAttribute("STR", true);
    for (std::vector<int>::iterator iter = pagenos[pageno].begin();
         iter != pagenos[pageno].end(); ++iter)
    {
        int from_pageno = *iter;
        if (o.verbose)
        {
            std::cout << "STR" << from_pageno << std::endl;
        }
        if (0 == fo.count(from_pageno))
        {
            fo[from_pageno] =
                pdf.copyForeignObject(
                    pages.at(from_pageno - 1).getFormXObjectForPage());
        }
        
        
        
        
        std::string name = resources.getUniqueResourceName("STR", min_suffix);
        std::string new_content = dest_page.placeFormXObject(
            fo[from_pageno], name,
            dest_page.getTrimBox().getArrayAsRectangle());
        if (! new_content.empty())
        {
            resources.mergeResources(
                QPDFObjectHandle::parse("STR"));
            resources.getKey("STR").replaceKey(name, fo[from_pageno]);
            ++min_suffix;
            content += new_content;
        }
    }
    if (! content.empty())
    {
        if (before)
        {
            dest_page.addPageContents(
                QPDFObjectHandle::newStream(&pdf, content), true);
        }
        else
        {
            dest_page.addPageContents(
                QPDFObjectHandle::newStream(&pdf, "STR"), true);
            dest_page.addPageContents(
                QPDFObjectHandle::newStream(&pdf, "STR" + content), false);
        }
    }
}