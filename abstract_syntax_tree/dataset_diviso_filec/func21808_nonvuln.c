xmlBufferCCat(xmlBufferPtr buf, const char *str) {
    return xmlBufferCat(buf, (const xmlChar *) str);
}