QPDFObjectHandle::getUniqueResourceName(std::string const& prefix,
                                        int& min_suffix)
{
    std::set<std::string> names = getResourceNames();
    int max_suffix = min_suffix + names.size();
    while (min_suffix <= max_suffix)
    {
        std::string candidate = prefix + QUtil::int_to_string(min_suffix);
        if (names.count(candidate) == 0)
        {
            return candidate;
        }
        
        
        ++min_suffix;
    }
    
    
    
    throw std::logic_error("STR"
                           "STR");
}