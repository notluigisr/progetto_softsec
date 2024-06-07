static void do_json_pages(QPDF& pdf, Options& o, JSON& j)
{
    JSON j_pages = j.addDictionaryMember("STR", JSON::makeArray());
    QPDFPageDocumentHelper pdh(pdf);
    QPDFPageLabelDocumentHelper pldh(pdf);
    QPDFOutlineDocumentHelper odh(pdf);
    pdh.pushInheritedAttributesToPage();
    std::vector<QPDFPageObjectHelper> pages = pdh.getAllPages();
    size_t pageno = 0;
    for (std::vector<QPDFPageObjectHelper>::iterator iter = pages.begin();
         iter != pages.end(); ++iter, ++pageno)
    {
        JSON j_page = j_pages.addArrayElement(JSON::makeDictionary());
        QPDFPageObjectHelper& ph(*iter);
        QPDFObjectHandle page = ph.getObjectHandle();
        j_page.addDictionaryMember("STR", page.getJSON());
        JSON j_images = j_page.addDictionaryMember(
            "STR", JSON::makeArray());
        std::map<std::string, QPDFObjectHandle> images =
            ph.getPageImages();
        for (std::map<std::string, QPDFObjectHandle>::iterator iter =
                 images.begin();
             iter != images.end(); ++iter)
        {
            JSON j_image = j_images.addArrayElement(JSON::makeDictionary());
            j_image.addDictionaryMember(
                "STR", JSON::makeString((*iter).first));
            QPDFObjectHandle image = (*iter).second;
            QPDFObjectHandle dict = image.getDict();
            j_image.addDictionaryMember("STR", image.getJSON());
            j_image.addDictionaryMember(
                "STR").getJSON());
            j_image.addDictionaryMember(
                "STR").getJSON());
            j_image.addDictionaryMember(
                "STR").getJSON());
            j_image.addDictionaryMember(
                "STR").getJSON());
            QPDFObjectHandle filters = dict.getKey("STR").wrapInArray();
            j_image.addDictionaryMember(
                "STR", filters.getJSON());
            QPDFObjectHandle decode_parms = dict.getKey("STR");
            QPDFObjectHandle dp_array;
            if (decode_parms.isArray())
            {
                dp_array = decode_parms;
            }
            else
            {
                dp_array = QPDFObjectHandle::newArray();
                for (int i = 0; i < filters.getArrayNItems(); ++i)
                {
                    dp_array.appendItem(decode_parms);
                }
            }
            j_image.addDictionaryMember("STR", dp_array.getJSON());
            j_image.addDictionaryMember(
                "STR",
                JSON::makeBool(
                    image.pipeStreamData(0, 0, o.decode_level, true)));
        }
        j_page.addDictionaryMember("STR", j_images);
        JSON j_contents = j_page.addDictionaryMember(
            "STR", JSON::makeArray());
        std::vector<QPDFObjectHandle> content = ph.getPageContents();
        for (std::vector<QPDFObjectHandle>::iterator iter = content.begin();
             iter != content.end(); ++iter)
        {
            j_contents.addArrayElement((*iter).getJSON());
        }
        j_page.addDictionaryMember(
            "STR", pldh.getLabelForPage(pageno).getJSON());
        JSON j_outlines = j_page.addDictionaryMember(
            "STR", JSON::makeArray());
        std::list<QPDFOutlineObjectHelper> outlines =
            odh.getOutlinesForPage(page.getObjGen());
        for (std::list<QPDFOutlineObjectHelper>::iterator oiter =
                 outlines.begin();
             oiter != outlines.end(); ++oiter)
        {
            JSON j_outline = j_outlines.addArrayElement(JSON::makeDictionary());
            j_outline.addDictionaryMember(
                "STR", (*oiter).getObjectHandle().getJSON());
            j_outline.addDictionaryMember(
                "STR", JSON::makeString((*oiter).getTitle()));
            j_outline.addDictionaryMember(
                "STR", (*oiter).getDest().getJSON(true));
        }
        j_page.addDictionaryMember("STR", JSON::makeInt(1 + pageno));
    }
}