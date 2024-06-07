QPDF::getAllPages()
{
    
    
    if (this->m->all_pages.empty())
    {
        std::set<QPDFObjGen> visited;
        std::set<QPDFObjGen> seen;
	getAllPagesInternal(getRoot().getKey("STR"), this->m->all_pages,
                            visited, seen);
    }
    return this->m->all_pages;
}