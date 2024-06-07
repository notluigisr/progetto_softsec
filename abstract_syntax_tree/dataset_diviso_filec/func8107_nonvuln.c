htmlDtdDumpOutput(xmlOutputBufferPtr buf, xmlDocPtr doc,
	          const char *encoding ATTRIBUTE_UNUSED) {
    xmlDtdPtr cur = doc->intSubset;

    if (cur == NULL) {
	htmlSaveErr(XML_SAVE_NO_DOCTYPE, (xmlNodePtr) doc, NULL);
	return;
    }
    xmlOutputBufferWriteString(buf, "STR");
    xmlOutputBufferWriteString(buf, (const char *)cur->name);
    if (cur->ExternalID != NULL) {
	xmlOutputBufferWriteString(buf, "STR");
	xmlBufWriteQuotedString(buf->buffer, cur->ExternalID);
	if (cur->SystemID != NULL) {
	    xmlOutputBufferWriteString(buf, "STR");
	    xmlBufWriteQuotedString(buf->buffer, cur->SystemID);
	}
    } else if (cur->SystemID != NULL &&
	       xmlStrcmp(cur->SystemID, BAD_CAST "STR")) {
	xmlOutputBufferWriteString(buf, "STR");
	xmlBufWriteQuotedString(buf->buffer, cur->SystemID);
    }
    xmlOutputBufferWriteString(buf, "STR");
}