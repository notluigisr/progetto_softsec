ArgParser::handleArgFileArguments()
{
    
    
    
    
    new_argv.push_back(PointerHolder<char>(true, QUtil::copy_string(argv[0])));
    for (int i = 1; i < argc; ++i)
    {
        char* argfile = 0;
        if ((strlen(argv[i]) > 1) && (argv[i][0] == '@'))
        {
            try
            {
                argfile = 1 + argv[i];
                if (strcmp(argfile, "STR") != 0)
                {
                    fclose(QUtil::safe_fopen(argfile, "STR"));
                }
            }
            catch (std::runtime_error&)
            {
                
                argfile = 0;
            }
        }
        if (argfile)
        {
            readArgsFromFile(1+argv[i]);
        }
        else
        {
            new_argv.push_back(
                PointerHolder<char>(true, QUtil::copy_string(argv[i])));
        }
    }
    argv_ph = PointerHolder<char*>(true, new char*[1+new_argv.size()]);
    argv = argv_ph.getPointer();
    for (size_t i = 0; i < new_argv.size(); ++i)
    {
        argv[i] = new_argv.at(i).getPointer();
    }
    argc = static_cast<int>(new_argv.size());
    argv[argc] = 0;
}