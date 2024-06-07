xmlReaderForIO(xmlInputReadCallback ioread, xmlInputCloseCallback ioclose,
               void *ioctx, const char *URL, const char *encoding,
               int options)
{
    xmlTextReaderPtr reader;
    xmlParserInputBufferPtr input;

    if (ioread == NULL)
        return (NULL);

    input = xmlParserInputBufferCreateIO(ioread, ioclose, ioctx,
                                         XML_CHAR_ENCODING_NONE);
    if (input == NULL) {
        if (ioclose != NULL)
            ioclose(ioctx);
        return (NULL);
    }
    reader = xmlNewTextReader(input, URL);
    if (reader == NULL) {
        xmlFreeParserInputBuffer(input);
        return (NULL);
    }
    reader->allocs |= XML_TEXTREADER_INPUT;
    xmlTextReaderSetup(reader, NULL, URL, encoding, options);
    return (reader);
}