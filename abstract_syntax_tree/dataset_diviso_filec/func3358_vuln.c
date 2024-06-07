QPDF::flattenPagesTree()
{
    
    

    if (! this->m->pageobj_to_pages_pos.empty())
    {
        return;
    }

    
    
    pushInheritedAttributesToPage(true, true);

    QPDFObjectHandle pages = getRoot().getKey("STR");

    int const len = this->m->all_pages.size();
    for (int pos = 0; pos < len; ++pos)
    {
        
        insertPageobjToPage(this->m->all_pages.at(pos), pos, true);
        this->m->all_pages.at(pos).replaceKey("STR", pages);
    }

    pages.replaceKey("STR", QPDFObjectHandle::newArray(this->m->all_pages));
    
    if (pages.getKey("STR").getIntValue() != len)
    {
        throw std::logic_error("STR");
    }
}