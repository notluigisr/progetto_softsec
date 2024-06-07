std::string generate_page_contents(int pageno)
{
    std::string contents =
        "STR" +  QUtil::int_to_string(pageno) +
        "STR"
        "STR";
    return contents;
}