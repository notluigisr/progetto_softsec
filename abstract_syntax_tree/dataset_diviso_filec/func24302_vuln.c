  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    offset = be64toh (h->sbuf.sr.payload.offset_hole.offset);
    length = be32toh (h->sbuf.sr.payload.offset_hole.length);

    assert (cmd); 

    assert (cmd->data && cmd->type == NBD_CMD_READ);
    cmd->data_seen = true;

    
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

    
    memset (cmd->data + offset, 0, length);
    if (CALLBACK_IS_NOT_NULL (cmd->cb.fn.chunk)) {
      int error = cmd->error;

      if (CALL_CALLBACK (cmd->cb.fn.chunk,
                         cmd->data + offset, length,
                         cmd->offset + offset,
                         LIBNBD_READ_HOLE, &error) == -1)
        if (cmd->error == 0)
          cmd->error = error ? error : EPROTO;
    }

    SET_NEXT_STATE(%FINISH);
  }