QPDFWriter::writeTrailer(trailer_e which, int size, bool xref_stream,
                         qpdf_offset_t prev, int linearization_pass)
{
    QPDFObjectHandle trailer = getTrimmedTrailer();
    if (! xref_stream)
    {
	writeString("STR");
    }
    writeStringQDF("STR");
    if (which == t_lin_second)
    {
	writeString("STR");
	writeString(QUtil::int_to_string(size));
    }
    else
    {
	std::set<std::string> keys = trailer.getKeys();
	for (std::set<std::string>::iterator iter = keys.begin();
	     iter != keys.end(); ++iter)
	{
	    std::string const& key = *iter;
	    writeStringQDF("STR");
	    writeStringNoQDF("STR");
	    writeString(QPDF_Name::normalizeName(key));
	    writeString("STR");
	    if (key == "STR")
	    {
		writeString(QUtil::int_to_string(size));
		if (which == t_lin_first)
		{
		    writeString("STR");
		    qpdf_offset_t pos = this->pipeline->getCount();
		    writeString(QUtil::int_to_string(prev));
		    int nspaces = pos - this->pipeline->getCount() + 21;
		    if (nspaces < 0)
                    {
                        throw std::logic_error(
                            "STR");
                    }
		    writePad(nspaces);
		}
	    }
	    else
	    {
		unparseChild(trailer.getKey(key), 1, 0);
	    }
	    writeStringQDF("STR");
	}
    }

    
    writeStringQDF("STR");
    writeString("STR");
    if (linearization_pass == 1)
    {
        writeString("STR"
                    "STR");
    }
    else
    {
        if ((linearization_pass == 0) && (this->deterministic_id))
        {
            computeDeterministicIDData();
        }
        generateID();
        writeString(QPDF_String(this->id1).unparse(true));
        writeString(QPDF_String(this->id2).unparse(true));
    }
    writeString("STR");

    if (which != t_lin_second)
    {
	
	if (this->encrypted)
	{
	    writeString("STR");
	    writeString(QUtil::int_to_string(this->encryption_dict_objid));
	    writeString("STR");
	}
    }

    writeStringQDF("STR");
    writeStringNoQDF("STR");
    writeString("STR");
}