static void xar_get_checksum_values(xmlTextReaderPtr reader, unsigned char ** cksum, int * hash)
{
    xmlChar * style = xmlTextReaderGetAttribute(reader, (const xmlChar *)"STR");
    const xmlChar * xmlval;

    *hash = XAR_CKSUM_NONE;
    if (style == NULL) {
        cli_dbgmsg("STR"
                   "STR");
    } else {
        cli_dbgmsg("STR", style);        
        if (0 == xmlStrcasecmp(style, (const xmlChar *)"STR")) {
            *hash = XAR_CKSUM_SHA1;
        } else if (0 == xmlStrcasecmp(style, (const xmlChar *)"STR")) {
            *hash = XAR_CKSUM_MD5;
        } else {
            cli_dbgmsg("STR", style);
            *hash = XAR_CKSUM_OTHER;
        }
    }
    if (style != NULL)
        xmlFree(style);

    if (xmlTextReaderRead(reader) == 1 && xmlTextReaderNodeType(reader) == XML_READER_TYPE_TEXT) {
        xmlval = xmlTextReaderConstValue(reader);
        if (xmlval) {
            *cksum = xmlStrdup(xmlval); 
            cli_dbgmsg("STR", *cksum);
        } else {
            *cksum = NULL;
            cli_dbgmsg("STR");           
        }
    }
    else
        cli_dbgmsg("STR");
}