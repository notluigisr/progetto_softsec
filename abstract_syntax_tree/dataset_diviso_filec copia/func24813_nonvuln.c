xmlReaderForMemory(const char *buffer, int size, const char *URL,
                   const char *encoding, int options)
{
    xmlTextReaderPtr reader;
    xmlParserInputBufferPtr buf;

    buf = xmlParserInputBufferCreateStatic(buffer, size,
                                      XML_CHAR_ENCODING_NONE);
    if (buf == NULL) {
        return (NULL);
    }
    reader = xmlNewTextReader(buf, URL);
    if (reader == NULL) {
        xmlFreeParserInputBuffer(buf);
        return (NULL);
    }
    reader->allocs |= XML_TEXTREADER_INPUT;
    xmlTextReaderSetup(reader, NULL, URL, encoding, options);
    return (reader);
}