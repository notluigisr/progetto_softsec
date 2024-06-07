static ssize_t inbound_frame_compute_pad(nghttp2_inbound_frame *iframe) {
  size_t padlen;

  
  padlen = (size_t)(iframe->sbuf.pos[0] + 1);

  DEBUGF("STR", padlen);

  
  if (padlen - 1 > iframe->payloadleft) {
    return -1;
  }

  iframe->padlen = padlen;

  return (ssize_t)padlen;
}