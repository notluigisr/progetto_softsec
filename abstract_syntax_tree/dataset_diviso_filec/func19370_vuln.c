JSON::encode_string(std::string const& str)
{
    std::string result;
    size_t len = str.length();
    for (size_t i = 0; i < len; ++i)
    {
        unsigned char ch = static_cast<unsigned char>(str.at(i));
        switch (ch)
        {
          case '\\':
            result += "STR";
            break;
          case '\"':
            result += "STR";
            break;
          case '\b':
            result += "STR";
            break;
          case '\n':
            result += "STR";
            break;
          case '\r':
            result += "STR";
            break;
          case '\t':
            result += "STR";
            break;
          default:
            if (ch < 32)
            {
                result += "STR" + QUtil::int_to_string_base(ch, 16, 4);
            }
            else
            {
                result.append(1, ch);
            }
        }
    }
    return result;
}