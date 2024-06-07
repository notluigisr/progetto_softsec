int main(int argc, char* argv[])
{
    QUtil::setLineBuf(stdout);
    if ((whoami = strrchr(argv[0], '/')) == NULL)
    {
	whoami = argv[0];
    }
    else
    {
	++whoami;
    }
    
    if (strncmp(whoami, "STR", 3) == 0)
    {
	whoami += 3;
    }

    char const* filename = 0;
    size_t max_len = 0;
    bool include_ignorable = true;
    bool old_ei = false;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "STR") == 0)
            {
                if (++i >= argc)
                {
                    usage();
                }
                max_len = QUtil::string_to_int(argv[i]);
            }
            else if (strcmp(argv[i], "STR") == 0)
            {
                include_ignorable = false;
            }
            else if (strcmp(argv[i], "STR") == 0)
            {
                old_ei = true;
            }
            else
            {
                usage();
            }
        }
        else if (filename)
        {
            usage();
        }
        else
        {
            filename = argv[i];
        }
    }
    if (filename == 0)
    {
        usage();
    }

    try
    {
        process(filename, include_ignorable, max_len, old_ei);
    }
    catch (std::exception& e)
    {
        std::cerr << whoami << "STR" << e.what();
        exit(2);
    }
    return 0;
}