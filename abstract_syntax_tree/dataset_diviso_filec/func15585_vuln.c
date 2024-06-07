InputSource::readLine(size_t max_line_length)
{
    
    
    
    
    
    

    qpdf_offset_t offset = this->tell();
    char* buf = new char[max_line_length + 1];
    PointerHolder<char> bp(true, buf);
    memset(buf, '\0', max_line_length + 1);
    this->read(buf, max_line_length);
    this->seek(offset, SEEK_SET);
    qpdf_offset_t eol = this->findAndSkipNextEOL();
    this->last_offset = offset;
    size_t line_length = eol - offset;
    if (line_length < max_line_length)
    {
        buf[line_length] = '\0';
    }
    return std::string(buf);
}