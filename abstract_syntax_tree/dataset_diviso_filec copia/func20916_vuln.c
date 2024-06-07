static void do_show_pages(QPDF& pdf, Options& o)
{
    QPDFPageDocumentHelper dh(pdf);
    std::vector<QPDFPageObjectHelper> pages = dh.getAllPages();
    int pageno = 0;
    for (std::vector<QPDFPageObjectHelper>::iterator iter = pages.begin();
         iter != pages.end(); ++iter)
    {
        QPDFPageObjectHelper& ph(*iter);
        QPDFObjectHandle page = ph.getObjectHandle();
        ++pageno;

        std::cout << "STR"
                  << page.getObjectID() << "STR"
                  << page.getGeneration() << "STR" << std::endl;
        if (o.show_page_images)
        {
            std::map<std::string, QPDFObjectHandle> images =
                ph.getPageImages();
            if (! images.empty())
            {
                std::cout << "STR" << std::endl;
                for (std::map<std::string,
                         QPDFObjectHandle>::iterator
                         iter = images.begin();
                     iter != images.end(); ++iter)
                {
                    std::string const& name = (*iter).first;
                    QPDFObjectHandle image = (*iter).second;
                    QPDFObjectHandle dict = image.getDict();
                    int width =
                        dict.getKey("STR").getIntValue();
                    int height =
                        dict.getKey("STR").getIntValue();
                    std::cout << "STR"
                              << image.unparse()
                              << "STR" << height
                              << std::endl;
                }
            }
        }

        std::cout << "STR" << std::endl;
        std::vector<QPDFObjectHandle> content =
            ph.getPageContents();
        for (std::vector<QPDFObjectHandle>::iterator iter =
                 content.begin();
             iter != content.end(); ++iter)
        {
            std::cout << "STR" << (*iter).unparse() << std::endl;
        }
    }
}