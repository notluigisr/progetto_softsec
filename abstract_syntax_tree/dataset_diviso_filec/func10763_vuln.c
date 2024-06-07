void pad_short_parameter(std::string& param, unsigned int max_len)
{
    if (param.length() < max_len)
    {
        QTC::TC("STR");
        param.append(max_len - param.length(), '\0');
    }
}