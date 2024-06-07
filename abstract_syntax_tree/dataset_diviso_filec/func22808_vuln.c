QPDF::parse_xrefFirst(std::string const& line,
                      int& obj, int& num, int& bytes)
{
    
    
    char const* p = line.c_str();
    char const* start = line.c_str();

    
    while (QUtil::is_space(*p))
    {
        ++p;
    }
    
    if (! QUtil::is_digit(*p))
    {
        return false;
    }
    
    std::string obj_str;
    while (QUtil::is_digit(*p))
    {
        obj_str.append(1, *p++);
    }
    
    if (! QUtil::is_space(*p))
    {
        return false;
    }
    
    while (QUtil::is_space(*p))
    {
        ++p;
    }
    
    if (! QUtil::is_digit(*p))
    {
        return false;
    }
    
    std::string num_str;
    while (QUtil::is_digit(*p))
    {
        num_str.append(1, *p++);
    }
    
    while (QUtil::is_space(*p))
    {
        ++p;
    }
    bytes = p - start;
    obj = QUtil::string_to_int(obj_str.c_str());
    num = QUtil::string_to_int(num_str.c_str());
    return true;
}