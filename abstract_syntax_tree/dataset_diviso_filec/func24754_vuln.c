  switch (recv_into_rbuf (h)) {
  case -1: SET_NEXT_STATE (%.DEAD); return 0;
  case 1:
    save_reply_state (h);
    SET_NEXT_STATE (%.READY);
    return 0;
  case 0:
    length = be32toh (h->sbuf.sr.structured_reply.length);
    msglen = be16toh (h->sbuf.sr.payload.error.error.len);
    if (msglen > length - sizeof h->sbuf.sr.payload.error.error ||
        msglen > sizeof h->sbuf.sr.payload.error.msg) {
      SET_NEXT_STATE (%.DEAD);
      set_error (0, "STR");
      return 0;
    }

    h->rbuf = h->sbuf.sr.payload.error.msg;
    h->rlen = msglen;
    SET_NEXT_STATE (%RECV_ERROR_MESSAGE);
  }