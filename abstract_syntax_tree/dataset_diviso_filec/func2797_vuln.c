QPDF::outputLengthNextN(
    int in_object, int n,
    std::map<int, qpdf_offset_t> const& lengths,
    std::map<int, int> const& obj_renumber)
{
    
    
    

    if (obj_renumber.count(in_object) == 0)
    {
        stopOnError("STR"
                    "STR");
    }
    int first = (*(obj_renumber.find(in_object))).second;
    int length = 0;
    for (int i = 0; i < n; ++i)
    {
	if (lengths.count(first + i) == 0)
        {
            stopOnError("STR"
                        "STR");
        }
	length += (*(lengths.find(first + i))).second;
    }
    return length;
}