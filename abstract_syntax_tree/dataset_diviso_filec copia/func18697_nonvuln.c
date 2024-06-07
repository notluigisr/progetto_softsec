int vncws_decode_frame_payload(Buffer *input,
                               size_t *payload_remain, WsMask *payload_mask,
                               uint8_t **payload, size_t *payload_size)
{
    size_t i;
    uint32_t *payload32;

    *payload = input->buffer;
    
    if (input->offset < *payload_remain) {
        *payload_size = input->offset - (input->offset % 4);
    } else {
        *payload_size = *payload_remain;
    }
    if (*payload_size == 0) {
        return 0;
    }
    *payload_remain -= *payload_size;

    
    
    payload32 = (uint32_t *)(*payload);
    for (i = 0; i < *payload_size / 4; i++) {
        payload32[i] ^= payload_mask->u;
    }
    
    for (i *= 4; i < *payload_size; i++) {
        (*payload)[i] ^= payload_mask->c[i % 4];
    }

    return 1;
}