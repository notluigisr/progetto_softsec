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
    if ((length > 0) &&
        (buf.str().length() < QIntC::to_size(length)))
    {
	result.append(length - buf.str().length(), '0');
    }
    result += buf.str();
    if ((length < 0) && (buf.str().length() < QIntC::to_size(-length)))
    {
	result.append(-length - buf.str().length(), ' ');
    }
    return result;
}