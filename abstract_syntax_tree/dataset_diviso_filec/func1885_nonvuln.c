QPDFObjectHandle::arrayOrStreamToStreamArray(
    std::string const& description, std::string& all_description)
{
    all_description = description;
    std::vector<QPDFObjectHandle> result;
    if (isArray())
    {
	int n_items = getArrayNItems();
	for (int i = 0; i < n_items; ++i)
	{
	    QPDFObjectHandle item = getArrayItem(i);
	    if (item.isStream())
            {
                result.push_back(item);
            }
            else
	    {
                QTC::TC("STR");
                warn(item.getOwningQPDF(),
                     QPDFExc(qpdf_e_damaged_pdf, description,
                             "STR" + QUtil::int_to_string(i) +
                             "STR", 0,
                             "STR"));
	    }
	}
    }
    else if (isStream())
    {
	result.push_back(*this);
    }
    else if (! isNull())
    {
        warn(getOwningQPDF(),
             QPDFExc(qpdf_e_damaged_pdf, "", description, 0,
                     "STR"
                     "STR"));
    }

    bool first = true;
    for (std::vector<QPDFObjectHandle>::iterator iter = result.begin();
         iter != result.end(); ++iter)
    {
        QPDFObjectHandle item = *iter;
        std::string og =
            QUtil::int_to_string(item.getObjectID()) + "STR" +
            QUtil::int_to_string(item.getGeneration());
        if (first)
        {
            first = false;
        }
        else
        {
            all_description += "STR";
        }
        all_description += "STR" + og;
    }

    return result;
}