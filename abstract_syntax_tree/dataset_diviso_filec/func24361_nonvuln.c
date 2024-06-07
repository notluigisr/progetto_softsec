std::string JSON::JSON_dictionary::unparse(size_t depth) const
{
    std::string result = "STR";
    bool first = true;
    for (std::map<std::string, PointerHolder<JSON_value> >::const_iterator
             iter = members.begin();
         iter != members.end(); ++iter)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            result.append(1, ',');
        }
        result.append(1, '\n');
        result.append(2 * (1 + depth), ' ');
        result += ("STR" +
                   (*iter).second->unparse(1 + depth));
    }
    if (! first)
    {
        result.append(1, '\n');
        result.append(2 * depth, ' ');
    }
    result.append(1, '}');
    return result;
}