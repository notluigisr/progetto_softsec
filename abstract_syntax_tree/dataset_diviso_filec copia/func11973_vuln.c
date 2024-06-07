static int tight_compress_data(VncState *vs, int stream_id, size_t bytes,
                               int level, int strategy)
{
    z_streamp zstream = &vs->tight.stream[stream_id];
    int previous_out;

    if (bytes < VNC_TIGHT_MIN_TO_COMPRESS) {
        vnc_write(vs, vs->tight.tight.buffer, vs->tight.tight.offset);
        return bytes;
    }

    if (tight_init_stream(vs, stream_id, level, strategy)) {
        return -1;
    }

    
    buffer_reserve(&vs->tight.zlib, bytes + 64);

    
    zstream->next_in = vs->tight.tight.buffer;
    zstream->avail_in = vs->tight.tight.offset;
    zstream->next_out = vs->tight.zlib.buffer + vs->tight.zlib.offset;
    zstream->avail_out = vs->tight.zlib.capacity - vs->tight.zlib.offset;
    previous_out = zstream->avail_out;
    zstream->data_type = Z_BINARY;

    
    if (deflate(zstream, Z_SYNC_FLUSH) != Z_OK) {
        fprintf(stderr, "STR");
        return -1;
    }

    vs->tight.zlib.offset = vs->tight.zlib.capacity - zstream->avail_out;
    
    bytes = previous_out - zstream->avail_out;

    tight_send_compact_size(vs, bytes);
    vnc_write(vs, vs->tight.zlib.buffer, bytes);

    buffer_reset(&vs->tight.zlib);

    return bytes;
}