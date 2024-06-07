static QEMUCursor *qxl_cursor(PCIQXLDevice *qxl, QXLCursor *cursor,
                              uint32_t group_id)
{
    QEMUCursor *c;
    uint8_t *and_mask, *xor_mask;
    size_t size;

    c = cursor_alloc(cursor->header.width, cursor->header.height);
    c->hot_x = cursor->header.hot_spot_x;
    c->hot_y = cursor->header.hot_spot_y;
    switch (cursor->header.type) {
    case SPICE_CURSOR_TYPE_MONO:
        
        size = 2 * cursor_get_mono_bpl(c) * c->height;
        if (size != cursor->data_size) {
            fprintf(stderr, "STR",
                    __func__, c->width, c->height, cursor->data_size);
            goto fail;
        }
        and_mask = cursor->chunk.data;
        xor_mask = and_mask + cursor_get_mono_bpl(c) * c->height;
        cursor_set_mono(c, 0xffffff, 0x000000, xor_mask, 1, and_mask);
        if (qxl->debug > 2) {
            cursor_print_ascii_art(c, "STR");
        }
        break;
    case SPICE_CURSOR_TYPE_ALPHA:
        size = sizeof(uint32_t) * c->width * c->height;
        qxl_unpack_chunks(c->data, size, qxl, &cursor->chunk, group_id);
        if (qxl->debug > 2) {
            cursor_print_ascii_art(c, "STR");
        }
        break;
    default:
        fprintf(stderr, "STR",
                __func__, cursor->header.type);
        goto fail;
    }
    return c;

fail:
    cursor_put(c);
    return NULL;
}