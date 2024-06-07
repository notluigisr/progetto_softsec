  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    length = be32toh (h->sbuf.sr.structured_reply.length);

    assert (cmd); 
    assert (cmd->type == NBD_CMD_BLOCK_STATUS);
    assert (CALLBACK_IS_NOT_NULL (cmd->cb.fn.extent));
    assert (h->bs_entries);
    assert (length >= 12);

    
    for (i = 0; i < length/4; ++i)
      h->bs_entries[i] = be32toh (h->bs_entries[i]);

    
    context_id = h->bs_entries[0];
    for (meta_context = h->meta_contexts;
         meta_context;
         meta_context = meta_context->next)
      if (context_id == meta_context->context_id)
        break;

    if (meta_context) {
      
      int error = cmd->error;

      if (CALL_CALLBACK (cmd->cb.fn.extent,
                         meta_context->name, cmd->offset,
                         &h->bs_entries[1], (length-4) / 4,
                         &error) == -1)
        if (cmd->error == 0)
          cmd->error = error ? error : EPROTO;
    }
    else
      
      debug (h, "STR" PRIu32,
             context_id);

    SET_NEXT_STATE(%FINISH);
  }