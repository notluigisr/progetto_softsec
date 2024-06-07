static int on_header(nghttp2_session *ngh2, const nghttp2_frame *frame,
                     const uint8_t *namearg, size_t nlen,
                     const uint8_t *valuearg, size_t vlen, uint8_t flags,
                     void *user_data) 
{
    h2_proxy_session *session = user_data;
    h2_proxy_stream *stream;
    const char *n = (const char*)namearg;
    const char *v = (const char*)valuearg;
    
    (void)session;
    if (frame->hd.type == NGHTTP2_HEADERS && nlen) {
        stream = nghttp2_session_get_stream_user_data(ngh2, frame->hd.stream_id);
        if (stream) {
            if (h2_proxy_stream_add_header_out(stream, n, nlen, v, vlen)) {
                return NGHTTP2_ERR_CALLBACK_FAILURE;
            }
        }
    }
    else if (frame->hd.type == NGHTTP2_PUSH_PROMISE) {
    }
    
    return 0;
}