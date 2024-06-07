int usbredirparser_serialize(struct usbredirparser *parser_pub,
                             uint8_t **state_dest, int *state_len)
{
    struct usbredirparser_priv *parser =
        (struct usbredirparser_priv *)parser_pub;
    struct usbredirparser_buf *wbuf;
    uint8_t *write_buf_count_pos, *state = NULL, *pos = NULL;
    uint32_t write_buf_count = 0, len, remain = 0;

    *state_dest = NULL;
    *state_len = 0;

    if (serialize_int(parser, &state, &pos, &remain,
                                   USBREDIRPARSER_SERIALIZE_MAGIC, "STR"))
        return -1;

    
    if (serialize_int(parser, &state, &pos, &remain, 0, "STR"))
        return -1;

    if (serialize_data(parser, &state, &pos, &remain,
                       (uint8_t *)parser->our_caps,
                       USB_REDIR_CAPS_SIZE * sizeof(int32_t), "STR"))
        return -1;

    if (parser->have_peer_caps) {
        if (serialize_data(parser, &state, &pos, &remain,
                           (uint8_t *)parser->peer_caps,
                           USB_REDIR_CAPS_SIZE * sizeof(int32_t), "STR"))
            return -1;
    } else {
        if (serialize_int(parser, &state, &pos, &remain, 0, "STR"))
            return -1;
    }

    if (serialize_int(parser, &state, &pos, &remain, parser->to_skip, "STR"))
        return -1;

    if (serialize_data(parser, &state, &pos, &remain,
                       (uint8_t *)&parser->header, parser->header_read,
                       "STR"))
        return -1;

    if (serialize_data(parser, &state, &pos, &remain,
                       parser->type_header, parser->type_header_read,
                       "STR"))
        return -1;

    if (serialize_data(parser, &state, &pos, &remain,
                       parser->data, parser->data_read, "STR"))
        return -1;

    write_buf_count_pos = pos;
    
    if (serialize_int(parser, &state, &pos, &remain, 0, "STR"))
        return -1;

    wbuf = parser->write_buf;
    while (wbuf) {
        if (serialize_data(parser, &state, &pos, &remain,
                           wbuf->buf + wbuf->pos, wbuf->len - wbuf->pos,
                           "STR"))
            return -1;
        write_buf_count++;
        wbuf = wbuf->next;
    }
    
    memcpy(write_buf_count_pos, &write_buf_count, sizeof(int32_t));

    
    len = pos - state;
    memcpy(state + sizeof(int32_t), &len, sizeof(int32_t));

    *state_dest = state;
    *state_len = len;

    return 0;
}