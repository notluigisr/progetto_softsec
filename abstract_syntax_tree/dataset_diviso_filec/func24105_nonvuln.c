int_to_string_base_internal(T num, int base, int length)
{
    
    
    
    
    if (! ((base == 8) || (base == 10) || (base == 16)))
    {
        throw std::logic_error(
            "STR");
    }
    std::ostringstream buf;
    buf << std::setbase(base) << std::nouppercase << num;
    std::string result;
    int str_length = QIntC::to_int(buf.str().length());
    if ((length > 0) && (str_length < length))
    {
	result.append(QIntC::to_size(length - str_length), '0');
    }
    result += buf.str();
    if ((length < 0) && (str_length < -length))
    {
	result.append(QIntC::to_size(-length - str_length), ' ');
    }
    return result;
}