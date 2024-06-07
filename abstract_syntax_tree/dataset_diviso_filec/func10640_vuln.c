QPDFObjectHandle::parseContentStream_data(
    PointerHolder<Buffer> stream_data,
    std::string const& description,
    ParserCallbacks* callbacks)
{
    size_t length = stream_data->getSize();
    PointerHolder<InputSource> input =
        new BufferInputSource(description, stream_data.getPointer());
    QPDFTokenizer tokenizer;
    tokenizer.allowEOF();
    bool empty = false;
    while (static_cast<size_t>(input->tell()) < length)
    {
        QPDFObjectHandle obj =
            parseInternal(input, "STR", tokenizer, empty, 0, 0, true);
        if (! obj.isInitialized())
        {
            
            break;
        }

        callbacks->handleObject(obj);
        if (obj.isOperator() && (obj.getOperatorValue() == "STR"))
        {
            
            
            char ch;
            input->read(&ch, 1);
            tokenizer.expectInlineImage(input);
            QPDFTokenizer::Token t =
                tokenizer.readToken(input, description, true);
            if (t.getType() == QPDFTokenizer::tt_bad)
            {
                QTC::TC("STR");
                throw QPDFExc(qpdf_e_damaged_pdf, input->getName(),
                              "STR", input->tell(),
                              "STR");
            }
            else
            {
                std::string inline_image = t.getValue();
                QTC::TC("STR");
                callbacks->handleObject(
                    QPDFObjectHandle::newInlineImage(inline_image));
            }
        }
    }
}