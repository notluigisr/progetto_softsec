xz_skip(xz_statep state, uint64_t len)
{
    unsigned n;

    
    while (len)
        
        if (state->have) {
            n = (uint64_t) state->have > len ?
                (unsigned) len : state->have;
            state->have -= n;
            state->next += n;
            state->pos += n;
            len -= n;
        }

    
        else if (state->eof && state->strm.avail_in == 0)
            break;

    
        else {
            
            if (xz_make(state) == -1)
                return -1;
        }
    return 0;
}