static int vnc_zlib_stop(VncState *vs)
{
    z_streamp zstream = &vs->zlib.stream;
    int previous_out;

    
    vs->zlib.zlib = vs->output;
    vs->output = vs->zlib.tmp;

    

    
    
    if (zstream->opaque != vs) {
        int err;

        VNC_DEBUG("STR");
        VNC_DEBUG("STR", zstream->opaque, vs);
        zstream->zalloc = vnc_zlib_zalloc;
        zstream->zfree = vnc_zlib_zfree;

        err = deflateInit2(zstream, vs->tight.compression, Z_DEFLATED, MAX_WBITS,
                           MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);

        if (err != Z_OK) {
            fprintf(stderr, "STR");
            return -1;
        }

        vs->zlib.level = vs->tight.compression;
        zstream->opaque = vs;
    }

    if (vs->tight.compression != vs->zlib.level) {
        if (deflateParams(zstream, vs->tight.compression,
                          Z_DEFAULT_STRATEGY) != Z_OK) {
            return -1;
        }
        vs->zlib.level = vs->tight.compression;
    }

    
    buffer_reserve(&vs->output, vs->zlib.zlib.offset + 64);

    
    zstream->next_in = vs->zlib.zlib.buffer;
    zstream->avail_in = vs->zlib.zlib.offset;
    zstream->next_out = vs->output.buffer + vs->output.offset;
    zstream->avail_out = vs->output.capacity - vs->output.offset;
    previous_out = zstream->avail_out;
    zstream->data_type = Z_BINARY;

    
    if (deflate(zstream, Z_SYNC_FLUSH) != Z_OK) {
        fprintf(stderr, "STR");
        return -1;
    }

    vs->output.offset = vs->output.capacity - zstream->avail_out;
    return previous_out - zstream->avail_out;
}