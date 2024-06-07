QPDF::removePage(QPDFObjectHandle page)
{
    int pos = findPage(page); 
    QTC::TC("STR",
            (pos == 0) ? 0 :                            
            (pos == static_cast<int>(
                this->m->all_pages.size() - 1)) ? 1 :   
            2);                                         

    QPDFObjectHandle pages = getRoot().getKey("STR");
    QPDFObjectHandle kids = pages.getKey("STR");

    kids.eraseItem(pos);
    int npages = kids.getArrayNItems();
    pages.replaceKey("STR", QPDFObjectHandle::newInteger(npages));
    this->m->all_pages.erase(this->m->all_pages.begin() + pos);
    assert(this->m->all_pages.size() == static_cast<size_t>(npages));
    this->m->pageobj_to_pages_pos.erase(page.getObjGen());
    assert(this->m->pageobj_to_pages_pos.size() == static_cast<size_t>(npages));
    for (int i = pos; i < npages; ++i)
    {
        insertPageobjToPage(this->m->all_pages.at(i), i, false);
    }
}