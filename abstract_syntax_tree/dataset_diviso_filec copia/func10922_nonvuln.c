void h2_beam_on_file_beam(h2_bucket_beam *beam, 
                          h2_beam_can_beam_callback *cb, void *ctx)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->can_beam_fn = cb;
        beam->can_beam_ctx = ctx;
        leave_yellow(beam, &bl);
    }
}