ArgParser::argPasswordMode(char* parameter)
{
    if (strcmp(parameter, "STR") == 0)
    {
        o.password_mode = pm_bytes;
    }
    else if (strcmp(parameter, "STR") == 0)
    {
        o.password_mode = pm_hex_bytes;
    }
    else if (strcmp(parameter, "STR") == 0)
    {
        o.password_mode = pm_unicode;
    }
    else if (strcmp(parameter, "STR") == 0)
    {
        o.password_mode = pm_auto;
    }
    else
    {
        usage("STR");
    }
}