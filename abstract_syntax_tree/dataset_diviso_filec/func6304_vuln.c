apr_status_t h2_stream_recv_frame(h2_stream *stream, int ftype, int flags, size_t frame_len)
{
    apr_status_t status = APR_SUCCESS;
    int new_state, eos = 0;

    new_state = on_frame_recv(stream->state, ftype);
    if (new_state < 0) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
                      H2_STRM_MSG(stream, "STR"), ftype);
        AP_DEBUG_ASSERT(new_state > S_XXX);
        return transit(stream, new_state);
    }
    
    switch (ftype) {
        case NGHTTP2_DATA:
            eos = (flags & NGHTTP2_FLAG_END_STREAM);
            break;
            
        case NGHTTP2_HEADERS:
            eos = (flags & NGHTTP2_FLAG_END_STREAM);
            if (stream->state == H2_SS_OPEN) {
                
                if (!eos) {
                    h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
                }
                stream->in_trailer_octets += frame_len;
            }
            else {
                
                ap_assert(stream->request == NULL);
                if (stream->rtmp == NULL) {
                    
                    return APR_EINVAL;
                }
                status = h2_request_end_headers(stream->rtmp, stream->pool, eos, frame_len);
                if (status != APR_SUCCESS) {
                    return status;
                }
                set_policy_for(stream, stream->rtmp);
                stream->request = stream->rtmp;
                stream->rtmp = NULL;
            }
            break;
            
        default:
            break;
    }
    status = transit(stream, new_state);
    if (status == APR_SUCCESS && eos) {
        status = transit(stream, on_event(stream, H2_SEV_CLOSED_R));
    }
    return status;
}