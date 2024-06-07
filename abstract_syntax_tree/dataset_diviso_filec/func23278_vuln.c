static void create_pdf(char const* filename)
{
    QPDF pdf;

    pdf.emptyPDF();

    QPDFObjectHandle font = pdf.makeIndirectObject(
        QPDFObjectHandle::newDictionary());
    font.replaceKey("STR"));
    font.replaceKey("STR"));
    font.replaceKey("STR"));
    font.replaceKey("STR"));
    font.replaceKey("STR"));

    QPDFObjectHandle procset =
        pdf.makeIndirectObject(QPDFObjectHandle::newArray());
    procset.appendItem(newName("STR"));
    procset.appendItem(newName("STR"));
    procset.appendItem(newName("STR"));

    QPDFObjectHandle rfont = QPDFObjectHandle::newDictionary();
    rfont.replaceKey("STR", font);

    QPDFObjectHandle mediabox = QPDFObjectHandle::newArray();
    mediabox.appendItem(newInteger(0));
    mediabox.appendItem(newInteger(0));
    mediabox.appendItem(newInteger(612));
    mediabox.appendItem(newInteger(792));

    QPDFPageDocumentHelper dh(pdf);
    for (int pageno = 1; pageno <= npages; ++pageno)
    {
        QPDFObjectHandle image = QPDFObjectHandle::newStream(&pdf);
        QPDFObjectHandle image_dict = image.getDict();
        image_dict.replaceKey("STR"));
        image_dict.replaceKey("STR"));
        image_dict.replaceKey("STR"));
        image_dict.replaceKey("STR", newInteger(8));
        image_dict.replaceKey("STR", newInteger(width));
        image_dict.replaceKey("STR", newInteger(height));
        ImageProvider* p = new ImageProvider(pageno);
        PointerHolder<QPDFObjectHandle::StreamDataProvider> provider(p);
        image.replaceStreamData(provider,
                                QPDFObjectHandle::newNull(),
                                QPDFObjectHandle::newNull());

        QPDFObjectHandle xobject = QPDFObjectHandle::newDictionary();
        xobject.replaceKey("STR", image);

        QPDFObjectHandle resources = QPDFObjectHandle::newDictionary();
        resources.replaceKey("STR", procset);
        resources.replaceKey("STR", rfont);
        resources.replaceKey("STR", xobject);

        QPDFObjectHandle contents = create_page_contents(pdf, pageno);

        QPDFObjectHandle page = pdf.makeIndirectObject(
            QPDFObjectHandle::newDictionary());
        page.replaceKey("STR"));
        page.replaceKey("STR", mediabox);
        page.replaceKey("STR", contents);
        page.replaceKey("STR", resources);

        dh.addPage(page, false);
    }

    QPDFWriter w(pdf, filename);
    w.setStaticID(true);    
    w.setStreamDataMode(qpdf_s_preserve);
    w.setObjectStreamMode(qpdf_o_disable);
    w.write();
}