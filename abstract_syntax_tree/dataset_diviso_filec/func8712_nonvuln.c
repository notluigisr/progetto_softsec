static void h2_session_in_flush(h2_session *session)
{
    int id;
    
    while ((id = h2_iq_shift(session->in_process)) > 0) {
        h2_stream *stream = get_stream(session, id);
        if (stream) {
            ap_assert(!stream->scheduled);
            if (h2_stream_prep_processing(stream) == APR_SUCCESS) {
                h2_mplx_process(session->mplx, stream, stream_pri_cmp, session);
            }
            else {
                h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
            }
        }
    }

    while ((id = h2_iq_shift(session->in_pending)) > 0) {
        h2_stream *stream = get_stream(session, id);
        if (stream) {
            h2_stream_flush_input(stream);
        }
    }
}