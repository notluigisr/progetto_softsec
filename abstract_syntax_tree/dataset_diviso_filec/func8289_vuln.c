QUtil::utf16_to_utf8(std::string const& val)
{
    std::string result;
    
    
    
    
    unsigned long codepoint = 0L;
    size_t len = val.length();
    size_t start = 0;
    if (is_utf16(val))
    {
        start += 2;
    }
    
    
    for (unsigned int i = start; i < len; i += 2)
    {
        
        
        
        
        
        
        unsigned short bits =
            (static_cast<unsigned char>(val.at(i)) << 8) +
            static_cast<unsigned char>(val.at(i+1));
        if ((bits & 0xFC00) == 0xD800)
        {
            codepoint = 0x10000 + ((bits & 0x3FF) << 10);
            continue;
        }
        else if ((bits & 0xFC00) == 0xDC00)
        {
            if (codepoint != 0)
            {
                QTC::TC("STR");
            }
            codepoint += bits & 0x3FF;
        }
        else
        {
            codepoint = bits;
        }

        result += QUtil::toUTF8(codepoint);
        codepoint = 0;
    }
    return result;
}