  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    error = be32toh (h->sbuf.sr.payload.error.error.error);
    type = be16toh (h->sbuf.sr.structured_reply.type);

    assert (cmd); 
    error = nbd_internal_errno_of_nbd_error (error);

    
    if (error == NBD_SUCCESS) {
      debug (h, "STR");
      error = NBD_EINVAL;
    }
    error = nbd_internal_errno_of_nbd_error (error);

    
    if (type == NBD_REPLY_TYPE_ERROR_OFFSET) {
      offset = be64toh (h->sbuf.sr.payload.error.offset);
      if (offset < cmd->offset || offset >= cmd->offset + cmd->count) {
        SET_NEXT_STATE (%.DEAD);
        set_error (0, "STR"
                   "STR"
                   "STR"
                   "STR",
                   offset, cmd->offset, cmd->count);
        return 0;
      }
      if (cmd->type == NBD_CMD_READ &&
          CALLBACK_IS_NOT_NULL (cmd->cb.fn.chunk)) {
        int scratch = error;

        
        if (CALL_CALLBACK (cmd->cb.fn.chunk,
                           cmd->data + (offset - cmd->offset),
                           0, offset, LIBNBD_READ_ERROR,
                           &scratch) == -1)
          if (cmd->error == 0)
            cmd->error = scratch;
      }
    }

    
    if (cmd->error == 0)
      cmd->error = error;

    SET_NEXT_STATE(%FINISH);
  }