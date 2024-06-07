QPDF::findStartxref()
{
    QPDFTokenizer::Token t = readToken(this->m->file);
    if (t == QPDFTokenizer::Token(QPDFTokenizer::tt_word, "STR"))
    {
        t = readToken(this->m->file);
        if (t.getType() == QPDFTokenizer::tt_integer)
        {
            
            this->m->file->seek(this->m->file->getLastOffset(), SEEK_SET);
            return true;
        }
    }
    return false;
}