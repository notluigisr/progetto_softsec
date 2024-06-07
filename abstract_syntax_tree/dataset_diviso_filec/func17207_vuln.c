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
    if (CALLBACK_IS_NOT_NULL (cmd->cb.fn.chunk)) {
      int error = cmd->error;

      if (CALL_CALLBACK (cmd->cb.fn.chunk, cmd->data + (offset - cmd->offset),
                         length - sizeof offset, offset,
                         LIBNBD_READ_DATA, &error) == -1)
        if (cmd->error == 0)
          cmd->error = error ? error : EPROTO;
    }

    SET_NEXT_STATE (%FINISH);
  }