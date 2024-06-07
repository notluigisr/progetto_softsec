Headers::Headers(Isolate* isolate,
                 Local<Context> context,
                 Local<Array> headers) {
  Local<Value> header_string = headers->Get(context, 0).ToLocalChecked();
  Local<Value> header_count = headers->Get(context, 1).ToLocalChecked();
  count_ = header_count.As<Uint32>()->Value();
  int header_string_len = header_string.As<String>()->Length();

  if (count_ == 0) {
    CHECK_EQ(header_string_len, 0);
    return;
  }

  
  
  
  buf_.AllocateSufficientStorage((alignof(nghttp2_nv) - 1) +
                                 count_ * sizeof(nghttp2_nv) +
                                 header_string_len);
  
  char* start = reinterpret_cast<char*>(
      ROUND_UP(reinterpret_cast<uintptr_t>(*buf_), alignof(nghttp2_nv)));
  char* header_contents = start + (count_ * sizeof(nghttp2_nv));
  nghttp2_nv* const nva = reinterpret_cast<nghttp2_nv*>(start);

  CHECK_LE(header_contents + header_string_len, *buf_ + buf_.length());
  CHECK_EQ(header_string.As<String>()
              ->WriteOneByte(reinterpret_cast<uint8_t*>(header_contents),
                             0, header_string_len,
                             String::NO_NULL_TERMINATION),
           header_string_len);

  size_t n = 0;
  char* p;
  for (p = header_contents; p < header_contents + header_string_len; n++) {
    if (n >= count_) {
      
      
      
      static uint8_t zero = '\0';
      nva[0].name = nva[0].value = &zero;
      nva[0].namelen = nva[0].valuelen = 1;
      count_ = 1;
      return;
    }

    nva[n].flags = NGHTTP2_NV_FLAG_NONE;
    nva[n].name = reinterpret_cast<uint8_t*>(p);
    nva[n].namelen = strlen(p);
    p += nva[n].namelen + 1;
    nva[n].value = reinterpret_cast<uint8_t*>(p);
    nva[n].valuelen = strlen(p);
    p += nva[n].valuelen + 1;
  }
}