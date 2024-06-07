static void stream_input_ev(void *ctx, h2_bucket_beam *beam)
{
    h2_stream *stream = ctx;
    h2_mplx *m = stream->session->mplx;
    apr_atomic_set32(&m->event_pending, 1); 
}