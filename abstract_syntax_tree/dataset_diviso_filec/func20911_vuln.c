QPDF::lengthNextN(int first_object, int n,
		  std::list<std::string>& errors)
{
    int length = 0;
    for (int i = 0; i < n; ++i)
    {
	QPDFObjGen og(first_object + i, 0);
	if (this->m->xref_table.count(og) == 0)
	{
	    errors.push_back(
		"STR" +
		QUtil::int_to_string(first_object + i) + "STR");
	}
	else
	{
	    if (this->m->obj_cache.count(og) == 0)
            {
                stopOnError("STR"
                            "STR");
            }
	    length += this->m->obj_cache[og].end_after_space -
		getLinearizationOffset(og);
	}
    }
    return length;
}