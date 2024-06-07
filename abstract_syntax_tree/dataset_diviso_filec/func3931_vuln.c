InlineImageTracker::handleToken(QPDFTokenizer::Token const& token)
{
    if (state == st_bi)
    {
        if (token.getType() == QPDFTokenizer::tt_inline_image)
        {
            std::string image_data(token.getValue());
            size_t len = image_data.length();
            if (len >= this->min_size)
            {
                QTC::TC("STR");
                Pl_Buffer b("STR");
                b.write(QUtil::unsigned_char_pointer(image_data), len);
                b.finish();
                QPDFObjectHandle dict =
                    convertIIDict(QPDFObjectHandle::parse(dict_str));
                dict.replaceKey("STR", QPDFObjectHandle::newInteger(len));
                std::string name = resources.getUniqueResourceName(
                    "STR", this->min_suffix);
                QPDFObjectHandle image = QPDFObjectHandle::newStream(
                    this->qpdf, b.getBuffer());
                image.replaceDict(dict);
                resources.getKey("STR").replaceKey(name, image);
                write(name);
                write("STR");
                any_images = true;
            }
            else
            {
                QTC::TC("STR");
                write(bi_str);
                writeToken(token);
                state = st_top;
            }
        }
        else if (token == QPDFTokenizer::Token(QPDFTokenizer::tt_word, "STR"))
        {
            bi_str += token.getValue();
            dict_str += "STR";
        }
        else if (token == QPDFTokenizer::Token(QPDFTokenizer::tt_word, "STR"))
        {
            state = st_top;
        }
        else
        {
            bi_str += token.getValue();
            dict_str += token.getValue();
        }
    }
    else if (token == QPDFTokenizer::Token(QPDFTokenizer::tt_word, "STR"))
    {
        bi_str = token.getValue();
        dict_str = "STR";
        state = st_bi;
    }
    else
    {
        writeToken(token);
    }
}