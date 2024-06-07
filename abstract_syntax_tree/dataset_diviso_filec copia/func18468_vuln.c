_tiffReadProc(thandle_t hdata, tdata_t buf, tsize_t size) {
    TIFFSTATE *state = (TIFFSTATE *)hdata;
    tsize_t to_read;

    TRACE(("STR", (int)size));
    dump_state(state);

    to_read = min(size, min(state->size, (tsize_t)state->eof) - (tsize_t)state->loc);
    TRACE(("STR", (int)to_read));

    _TIFFmemcpy(buf, (UINT8 *)state->data + state->loc, to_read);
    state->loc += (toff_t)to_read;

    TRACE(("STR", (uint)state->loc));
    return to_read;
}