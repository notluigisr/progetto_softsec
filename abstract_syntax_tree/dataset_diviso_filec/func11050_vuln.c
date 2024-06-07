QPDF::parse_xrefEntry(std::string const& line,
                      qpdf_offset_t& f1, int& f2, char& type)
{
    
    
    char const* p = line.c_str();

    
    bool invalid = false;
    while (QUtil::is_space(*p))
    {
        ++p;
        QTC::TC("STR");
        invalid = true;
    }
    
    if (! QUtil::is_digit(*p))
    {
        return false;
    }
    
    std::string f1_str;
    while (QUtil::is_digit(*p))
    {
        f1_str.append(1, *p++);
    }
    
    if (! QUtil::is_space(*p))
    {
        return false;
    }
    if (QUtil::is_space(*(p+1)))
    {
        QTC::TC("STR");
        invalid = true;
    }
    
    while (QUtil::is_space(*p))
    {
        ++p;
    }
    
    if (! QUtil::is_digit(*p))
    {
        return false;
    }
    
    std::string f2_str;
    while (QUtil::is_digit(*p))
    {
        f2_str.append(1, *p++);
    }
    
    if (! QUtil::is_space(*p))
    {
        return false;
    }
    if (QUtil::is_space(*(p+1)))
    {
        QTC::TC("STR");
        invalid = true;
    }
    
    while (QUtil::is_space(*p))
    {
        ++p;
    }
    if ((*p == 'f') || (*p == 'n'))
    {
        type = *p;
    }
    else
    {
        return false;
    }
    if ((f1_str.length() != 10) || (f2_str.length() != 5))
    {
        QTC::TC("STR");
        invalid = true;
    }

    if (invalid)
    {
        warn(QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
                     "STR",
                     this->m->file->getLastOffset(),
                     "STR"));
    }

    f1 = QUtil::string_to_ll(f1_str.c_str());
    f2 = atoi(f2_str.c_str());

    return true;
}