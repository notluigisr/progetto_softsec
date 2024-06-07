QPDF::optimize(std::map<int, int> const& object_stream_data,
	       bool allow_changes)
{
    if (! this->m->obj_user_to_objects.empty())
    {
	
	return;
    }

    
    
    
    QPDFObjectHandle root = getRoot();
    if (root.getKey("STR").isDictionary())
    {
        QPDFObjectHandle outlines = root.getKey("STR");
        if (! outlines.isIndirect())
        {
            QTC::TC("STR");
            root.replaceKey("STR", makeIndirectObject(outlines));
        }
    }

    
    
    pushInheritedAttributesToPage(allow_changes, false);

    
    int n = this->m->all_pages.size();
    for (int pageno = 0; pageno < n; ++pageno)
    {
        updateObjectMaps(ObjUser(ObjUser::ou_page, pageno),
                         this->m->all_pages.at(pageno));
    }

    
    std::set<std::string> keys = this->m->trailer.getKeys();
    for (std::set<std::string>::iterator iter = keys.begin();
	 iter != keys.end(); ++iter)
    {
	std::string const& key = *iter;
	if (key == "STR")
	{
	    
	}
	else
	{
	    updateObjectMaps(ObjUser(ObjUser::ou_trailer_key, key),
			     this->m->trailer.getKey(key));
	}
    }

    keys = root.getKeys();
    for (std::set<std::string>::iterator iter = keys.begin();
	 iter != keys.end(); ++iter)
    {
	
	
	
	
	
	

	std::string const& key = *iter;
	updateObjectMaps(ObjUser(ObjUser::ou_root_key, key),
			 root.getKey(key));
    }

    ObjUser root_ou = ObjUser(ObjUser::ou_root);
    QPDFObjGen root_og = QPDFObjGen(root.getObjGen());
    this->m->obj_user_to_objects[root_ou].insert(root_og);
    this->m->object_to_obj_users[root_og].insert(root_ou);

    filterCompressedObjects(object_stream_data);
}