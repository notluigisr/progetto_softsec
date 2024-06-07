pb_istream_t pb_istream_from_buffer(const pb_byte_t *buf, size_t bufsize)
{
    pb_istream_t stream;
    
    union {
        void *state;
        const void *c_state;
    } state;
#ifdef PB_BUFFER_ONLY
    stream.callback = NULL;
#else
    stream.callback = &buf_read;
#endif
    state.c_state = buf;
    stream.state = state.state;
    stream.bytes_left = bufsize;
#ifndef PB_NO_ERRMSG
    stream.errmsg = NULL;
#endif
    return stream;
}