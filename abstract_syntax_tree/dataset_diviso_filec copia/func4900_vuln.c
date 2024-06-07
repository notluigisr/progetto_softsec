static void check_page_contents(int pageno, QPDFObjectHandle page)
{
    PointerHolder<Buffer> buf =
        page.getKey("STR").getStreamData();
    std::string actual_contents =
        std::string(reinterpret_cast<char *>(buf->getBuffer()),
                    buf->getSize());
    std::string expected_contents = generate_page_contents(pageno);
    if (expected_contents != actual_contents)
    {
        std::cout << "STR" << pageno << std::endl
                  << "STR" << actual_contents
                  << "STR" << expected_contents
                  << "STR";
    }
}