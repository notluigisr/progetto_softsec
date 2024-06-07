apr_status_t h2_mplx_client_rst(h2_mplx *m, int stream_id)
{
    h2_stream *stream;
    apr_status_t status = APR_SUCCESS;
    
    H2_MPLX_ENTER_ALWAYS(m);
    stream = h2_ihash_get(m->streams, stream_id);
    if (stream && stream->task) {
        status = mplx_be_annoyed(m);
    }
    H2_MPLX_LEAVE(m);
    return status;
}