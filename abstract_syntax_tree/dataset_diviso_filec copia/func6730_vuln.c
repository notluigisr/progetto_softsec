static apr_status_t gset_decode_next(gset_decoder *decoder, apr_uint64_t *phash)
{
    apr_uint64_t flex = 0, fixed = 0, delta;
    int i;
    
    
    while (1) {
        int bit = gset_decode_next_bit(decoder);
        if (bit == -1) {
            return APR_EINVAL;
        }
        if (!bit) {
            break;
        }
        ++flex;
    }
    
    for (i = 0; i < decoder->log2p; ++i) {
        int bit = gset_decode_next_bit(decoder);
        if (bit == -1) {
            return APR_EINVAL;
        }
        fixed = (fixed << 1) | bit;
    }
    
    delta = (flex << decoder->log2p) | fixed;
    *phash = delta + decoder->last_val;
    decoder->last_val = *phash;
    
    
    ap_log_perror(APLOG_MARK, GCSLOG_LEVEL, 0, decoder->pool,
                  "STR"
                  APR_UINT64_T_HEX_FMT"STR"APR_UINT64_T_HEX_FMT, 
                  *phash, delta, (int)flex, fixed);
                  
    return APR_SUCCESS;
}