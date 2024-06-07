xmlBufCCat(xmlBufPtr buf, const char *str) {
    return xmlBufCat(buf, (const xmlChar *) str);
}