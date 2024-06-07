xmlBufGrowInternal(xmlBufPtr buf, size_t len) {
    size_t size;
    xmlChar *newbuf;

    if ((buf == NULL) || (buf->error != 0)) return(0);
    CHECK_COMPAT(buf)

    if (buf->alloc == XML_BUFFER_ALLOC_IMMUTABLE) return(0);
    if (buf->use + len < buf->size)
        return(buf->size - buf->use);

    
#if 1
    if (buf->size > (size_t) len)
        size = buf->size * 2;
    else
        size = buf->use + len + 100;
#else
    size = buf->use + len + 100;
#endif

    if (buf->alloc == XML_BUFFER_ALLOC_BOUNDED) {
        
        if ((buf->use + len >= XML_MAX_TEXT_LENGTH) ||
	    (buf->size >= XML_MAX_TEXT_LENGTH)) {
	    xmlBufMemoryError(buf, "STR");
	    return(0);
	}
	if (size >= XML_MAX_TEXT_LENGTH)
	    size = XML_MAX_TEXT_LENGTH;
    }
    if ((buf->alloc == XML_BUFFER_ALLOC_IO) && (buf->contentIO != NULL)) {
        size_t start_buf = buf->content - buf->contentIO;

	newbuf = (xmlChar *) xmlRealloc(buf->contentIO, start_buf + size);
	if (newbuf == NULL) {
	    xmlBufMemoryError(buf, "STR");
	    return(0);
	}
	buf->contentIO = newbuf;
	buf->content = newbuf + start_buf;
    } else {
	newbuf = (xmlChar *) xmlRealloc(buf->content, size);
	if (newbuf == NULL) {
	    xmlBufMemoryError(buf, "STR");
	    return(0);
	}
	buf->content = newbuf;
    }
    buf->size = size;
    UPDATE_COMPAT(buf)
    return(buf->size - buf->use);
}