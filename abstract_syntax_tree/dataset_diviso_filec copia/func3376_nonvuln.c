h2_stream *h2_mplx_stream_get(h2_mplx *m, int id)
{
    h2_stream *s = NULL;
    
    H2_MPLX_ENTER_ALWAYS(m);

    s = h2_ihash_get(m->streams, id);

    H2_MPLX_LEAVE(m);
    return s;
}