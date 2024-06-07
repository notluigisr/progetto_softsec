static int xar_get_numeric_from_xml_element(xmlTextReaderPtr reader, long * value)
{
    const xmlChar * numstr;
    if (xmlTextReaderRead(reader) == 1 && xmlTextReaderNodeType(reader) == XML_READER_TYPE_TEXT) {
        numstr = xmlTextReaderConstValue(reader);
        if (numstr) {
            *value = atol((const char *)numstr);
            if (*value < 0) {
                cli_dbgmsg("STR", *value);
                return CL_EFORMAT;
            }
            return CL_SUCCESS;
        }
    }
    cli_dbgmsg("STR");
    return CL_EFORMAT;
}