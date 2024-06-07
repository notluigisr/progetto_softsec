  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    length = be32toh (h->sbuf.sr.structured_reply.length);
    msglen = be16toh (h->sbuf.sr.payload.error.error.len);
    type = be16toh (h->sbuf.sr.structured_reply.type);

    length -= sizeof h->sbuf.sr.payload.error.error + msglen;

    if (msglen)
      debug (h, "STR", (int) msglen,
             h->sbuf.sr.payload.error.msg);

    
    h->rbuf = NULL;
    h->rlen = length;
    switch (type) {
    case NBD_REPLY_TYPE_ERROR:
      if (length != 0) {
        SET_NEXT_STATE (%.DEAD);
        set_error (0, "STR");
        return 0;
      }
      break;
    case NBD_REPLY_TYPE_ERROR_OFFSET:
      if (length != sizeof h->sbuf.sr.payload.error.offset) {
        SET_NEXT_STATE (%.DEAD);
        set_error (0, "STR");
        return 0;
      }
      h->rbuf = &h->sbuf.sr.payload.error.offset;
      break;
    }
    SET_NEXT_STATE (%RECV_ERROR_TAIL);
  }