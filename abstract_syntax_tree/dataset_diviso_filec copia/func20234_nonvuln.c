void add_page(QPDFPageDocumentHelper& dh, QPDFObjectHandle font,
              std::string const& color_space,
              std::string const& filter)
{
    QPDF& pdf(dh.getQPDF());

    
    
    
    
    
    ImageProvider* p = new ImageProvider(color_space, filter);
    PointerHolder<QPDFObjectHandle::StreamDataProvider> provider(p);
    size_t width = p->getWidth();
    size_t height = p->getHeight();
    QPDFObjectHandle image = QPDFObjectHandle::newStream(&pdf);
    image.replaceDict(QPDFObjectHandle::parse(
                          "STR"
                          "STR"
                          "STR"
                          "STR"
                          "STR"));
    QPDFObjectHandle image_dict = image.getDict();
    image_dict.replaceKey("STR", newName(color_space));
    image_dict.replaceKey("STR", newInteger(width));
    image_dict.replaceKey("STR", newInteger(height));

    
    image.replaceStreamData(provider,
                            QPDFObjectHandle::parse(filter),
                            QPDFObjectHandle::newNull());

    
    QPDFObjectHandle procset = QPDFObjectHandle::parse(
        "STR");

    QPDFObjectHandle rfont = QPDFObjectHandle::newDictionary();
    rfont.replaceKey("STR", font);

    QPDFObjectHandle xobject = QPDFObjectHandle::newDictionary();
    xobject.replaceKey("STR", image);

    QPDFObjectHandle resources = QPDFObjectHandle::newDictionary();
    resources.replaceKey("STR", procset);
    resources.replaceKey("STR", rfont);
    resources.replaceKey("STR", xobject);

    QPDFObjectHandle mediabox = QPDFObjectHandle::newArray();
    mediabox.appendItem(newInteger(0));
    mediabox.appendItem(newInteger(0));
    mediabox.appendItem(newInteger(612));
    mediabox.appendItem(newInteger(392));

    
    QPDFObjectHandle contents = createPageContents(
        pdf, color_space + "STR" + filter);

    
    QPDFObjectHandle page = pdf.makeIndirectObject(
        QPDFObjectHandle::newDictionary());
    page.replaceKey("STR"));
    page.replaceKey("STR", mediabox);
    page.replaceKey("STR", contents);
    page.replaceKey("STR", resources);

    
    dh.addPage(page, false);
}