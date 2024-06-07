QPDFObjectHandle::parseContentStream_internal(PointerHolder<Buffer> stream_data,
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
            parseInternal(input, "STR", tokenizer, empty,
                          0, 0, false, false, true);
        if (! obj.isInitialized())
        {
            
            break;
        }

        callbacks->handleObject(obj);
        if (obj.isOperator() && (obj.getOperatorValue() == "STR"))
        {
            
            
            char ch;
            input->read(&ch, 1);
            char buf[4];
            memset(buf, '\0', sizeof(buf));
            bool done = false;
            std::string inline_image;
            while (! done)
            {
                if (input->read(&ch, 1) == 0)
                {
                    QTC::TC("STR");
                    throw QPDFExc(qpdf_e_damaged_pdf, input->getName(),
                                  "STR", input->tell(),
                                  "STR");
                }
                inline_image += ch;
                memmove(buf, buf + 1, sizeof(buf) - 1);
                buf[sizeof(buf) - 1] = ch;
                if (strchr("STR", buf[0]) &&
                    (buf[1] == 'E') &&
                    (buf[2] == 'I') &&
                    strchr("STR", buf[3]))
                {
                    
                    done = true;
                    input->seek(-3, SEEK_CUR);
                    for (int i = 0; i < 4; ++i)
                    {
                        if (inline_image.length() > 0)
                        {
                            inline_image.erase(inline_image.length() - 1);
                        }
                    }
                }
            }
            QTC::TC("STR");
            callbacks->handleObject(
                QPDFObjectHandle::newInlineImage(inline_image));
        }
    }
}