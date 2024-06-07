QPDF::insertPage(QPDFObjectHandle newpage, int pos)
{
    
    

    flattenPagesTree();

    if (! newpage.isIndirect())
    {
        QTC::TC("STR");
        newpage = makeIndirectObject(newpage);
    }
    else if (newpage.getOwningQPDF() != this)
    {
        QTC::TC("STR");
        newpage.getOwningQPDF()->pushInheritedAttributesToPage();
        newpage = copyForeignObject(newpage);
    }
    else
    {
        QTC::TC("STR");
    }

    QTC::TC("STR",
            (pos == 0) ? 0 :                      
            (pos == static_cast<int>(this->m->all_pages.size())) ? 1 : 
            2);                                   

    QPDFObjectHandle pages = getRoot().getKey("STR");
    QPDFObjectHandle kids = pages.getKey("STR");
    assert ((pos >= 0) &&
            (static_cast<size_t>(pos) <= this->m->all_pages.size()));

    newpage.replaceKey("STR", pages);
    kids.insertItem(pos, newpage);
    int npages = kids.getArrayNItems();
    pages.replaceKey("STR", QPDFObjectHandle::newInteger(npages));
    this->m->all_pages.insert(this->m->all_pages.begin() + pos, newpage);
    assert(this->m->all_pages.size() == static_cast<size_t>(npages));
    for (int i = pos + 1; i < npages; ++i)
    {
        insertPageobjToPage(this->m->all_pages.at(i), i, false);
    }
    insertPageobjToPage(newpage, pos, true);
    assert(this->m->pageobj_to_pages_pos.size() == static_cast<size_t>(npages));
}