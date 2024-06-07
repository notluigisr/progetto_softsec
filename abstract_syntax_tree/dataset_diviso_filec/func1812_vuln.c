QPDFObjectHandle::parse(std::string const& object_str,
                        std::string const& object_description)
{
    PointerHolder<InputSource> input =
        new BufferInputSource("STR", object_str);
    QPDFTokenizer tokenizer;
    bool empty = false;
    QPDFObjectHandle result =
        parse(input, object_description, tokenizer, empty, 0, 0);
    size_t offset = input->tell();
    while (offset < object_str.length())
    {
        if (! isspace(object_str.at(offset)))
        {
            QTC::TC("STR");
            throw QPDFExc(qpdf_e_damaged_pdf, input->getName(),
                          object_description,
                          input->getLastOffset(),
                          "STR");
        }
        ++offset;
    }
    return result;
}