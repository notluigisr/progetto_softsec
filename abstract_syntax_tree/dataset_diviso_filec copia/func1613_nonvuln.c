_tiffSizeProc(thandle_t hdata) {
    TIFFSTATE *state = (TIFFSTATE *)hdata;

    TRACE(("STR"));
    dump_state(state);

    return (toff_t)state->size;
}