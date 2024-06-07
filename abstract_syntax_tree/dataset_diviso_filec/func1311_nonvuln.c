int ZEXPORT inflateValidate(strm, check)
z_streamp strm;
int check;
{
    struct inflate_state FAR *state;

    if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
    state = (struct inflate_state FAR *)strm->state;
    if (check)
        state->wrap |= 4;
    else
        state->wrap &= ~4;
    return Z_OK;
}