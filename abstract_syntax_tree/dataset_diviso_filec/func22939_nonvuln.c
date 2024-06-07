int llhttp__on_url(llhttp_t* s, const char* p, const char* endp) {
  int err;
  SPAN_CALLBACK_MAYBE(s, on_url, p, endp - p);
  return err;
}