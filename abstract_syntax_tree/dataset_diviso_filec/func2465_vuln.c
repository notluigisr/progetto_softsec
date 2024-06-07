  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    length = be32toh (h->sbuf.sr.structured_reply.length);
    offset = be64toh (h->sbuf.sr.payload.offset_data.offset);

    assert (cmd); 

    assert (cmd->data && cmd->type == NBD_CMD_READ);
    cmd->data_seen = true;

    
    length -= 8;

    
    if (offset < cmd->offset) {
      SET_NEXT_STATE (%.DEAD);
      set_error (0, "STR"
                 "STR"
                 "STR",
                 offset, cmd->offset);
      return 0;
    }
    
    offset -= cmd->offset;

    if (offset + length > cmd->count) {
      SET_NEXT_STATE (%.DEAD);
      set_error (0, "STR"
                 "STR"
                 "STR"
                 "STR",
                 offset, length, cmd->count);
      return 0;
    }

    
    h->rbuf = cmd->data + offset;
    h->rlen = length;
    SET_NEXT_STATE (%RECV_OFFSET_DATA_DATA);
  }