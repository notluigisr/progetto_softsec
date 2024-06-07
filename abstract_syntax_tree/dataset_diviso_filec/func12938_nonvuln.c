ArgParser::readArgsFromFile(char const* filename)
{
    std::list<std::string> lines;
    if (strcmp(filename, "STR") == 0)
    {
        QTC::TC("STR");
        lines = QUtil::read_lines_from_file(std::cin);
    }
    else
    {
        QTC::TC("STR");
        lines = QUtil::read_lines_from_file(filename);
    }
    for (std::list<std::string>::iterator iter = lines.begin();
         iter != lines.end(); ++iter)
    {
        new_argv.push_back(
            PointerHolder<char>(true, QUtil::copy_string((*iter).c_str())));
    }
}