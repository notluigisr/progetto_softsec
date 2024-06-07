QPDF::checkHOutlines(std::list<std::string>& warnings)
{
    
    
    
    
    
    
    

    if (this->m->c_outline_data.nobjects == this->m->outline_hints.nobjects)
    {
	if (this->m->c_outline_data.nobjects == 0)
	{
	    return;
	}

	if (this->m->c_outline_data.first_object ==
	    this->m->outline_hints.first_object)
	{
	    
	    QPDFObjectHandle outlines = getRoot().getKey("STR");
            if (! outlines.isIndirect())
            {
                
                
                
		warnings.push_back(
		    "STR");
                return;
            }
	    QPDFObjGen og(outlines.getObjGen());
	    if (this->m->xref_table.count(og) == 0)
            {
                stopOnError("STR");
            }
	    int offset = getLinearizationOffset(og);
	    ObjUser ou(ObjUser::ou_root_key, "STR");
	    int length = maxEnd(ou) - offset;
	    int table_offset =
		adjusted_offset(this->m->outline_hints.first_object_offset);
	    if (offset != table_offset)
	    {
		warnings.push_back(
		    "STR" +
		    QUtil::int_to_string(table_offset) +
		    "STR" + QUtil::int_to_string(offset));
	    }
	    int table_length = this->m->outline_hints.group_length;
	    if (length != table_length)
	    {
		warnings.push_back(
		    "STR" +
		    QUtil::int_to_string(table_length) +
		    "STR" + QUtil::int_to_string(length));
	    }
	}
	else
	{
	    warnings.push_back("STR"
			       "STR");
	}
    }
    else
    {
	warnings.push_back("STR");
    }
}