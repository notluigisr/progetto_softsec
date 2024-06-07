xmlParserInputGrow(xmlParserInputPtr in, int len) {
    int ret;
    size_t indx;
    const xmlChar *content;

    if ((in == NULL) || (len < 0)) return(-1);
#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext, "STR");
#endif
    if (in->buf == NULL) return(-1);
    if (in->base == NULL) return(-1);
    if (in->cur == NULL) return(-1);
    if (in->buf->buffer == NULL) return(-1);

    CHECK_BUFFER(in);

    indx = in->cur - in->base;
    if (xmlBufUse(in->buf->buffer) > (unsigned int) indx + INPUT_CHUNK) {

	CHECK_BUFFER(in);

        return(0);
    }
    if (in->buf->readcallback != NULL) {
	ret = xmlParserInputBufferGrow(in->buf, len);
    } else
        return(0);

    

    content = xmlBufContent(in->buf->buffer);
    if (in->base != content) {
        
	indx = in->cur - in->base;
	in->base = content;
	in->cur = &content[indx];
    }
    in->end = xmlBufEnd(in->buf->buffer);

    CHECK_BUFFER(in);

    return(ret);
}