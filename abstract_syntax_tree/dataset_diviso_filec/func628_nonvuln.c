QPDF::getAllPagesInternal(QPDFObjectHandle cur_pages,
                          std::vector<QPDFObjectHandle>& result,
                          std::set<QPDFObjGen>& visited,
                          std::set<QPDFObjGen>& seen)
{
    QPDFObjGen this_og = cur_pages.getObjGen();
    if (visited.count(this_og) > 0)
    {
        throw QPDFExc(
            qpdf_e_pages, this->m->file->getName(),
            this->m->last_object_description, 0,
            "STR");
    }
    visited.insert(this_og);
    std::string type;
    QPDFObjectHandle type_key = cur_pages.getKey("STR");
    if (type_key.isName())
    {
        type = type_key.getName();
    }
    else if (cur_pages.hasKey("STR"))
    {
        type = "STR";
    }
    else
    {
        type = "STR";
    }
    if (type == "STR")
    {
	QPDFObjectHandle kids = cur_pages.getKey("STR");
	int n = kids.getArrayNItems();
	for (int i = 0; i < n; ++i)
	{
            QPDFObjectHandle kid = kids.getArrayItem(i);
            if (! kid.isIndirect())
            {
                QTC::TC("STR");
                kid = makeIndirectObject(kid);
                kids.setArrayItem(i, kid);
            }
            else if (seen.count(kid.getObjGen()))
            {
                
                
                QTC::TC("STR");
                kid = makeIndirectObject(QPDFObjectHandle(kid).shallowCopy());
                kids.setArrayItem(i, kid);
            }
	    getAllPagesInternal(kid, result, visited, seen);
	}
    }
    else if (type == "STR")
    {
        seen.insert(this_og);
	result.push_back(cur_pages);
    }
    else
    {
	throw QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
		      this->m->last_object_description,
		      this->m->file->getLastOffset(),
		      "STR");
    }
    visited.erase(this_og);
}