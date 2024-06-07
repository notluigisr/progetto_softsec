Http2Session::Http2Session(Environment* env,
                           Local<Object> wrap,
                           nghttp2_session_type type)
    : AsyncWrap(env, wrap, AsyncWrap::PROVIDER_HTTP2SESSION),
      session_type_(type) {
  MakeWeak();
  statistics_.start_time = uv_hrtime();

  
  Http2Options opts(env, type);

  max_session_memory_ = opts.GetMaxSessionMemory();

  uint32_t maxHeaderPairs = opts.GetMaxHeaderPairs();
  max_header_pairs_ =
      type == NGHTTP2_SESSION_SERVER
          ? std::max(maxHeaderPairs, 4U)     
          : std::max(maxHeaderPairs, 1U);    

  max_outstanding_pings_ = opts.GetMaxOutstandingPings();
  max_outstanding_settings_ = opts.GetMaxOutstandingSettings();

  padding_strategy_ = opts.GetPaddingStrategy();

  bool hasGetPaddingCallback =
      padding_strategy_ != PADDING_STRATEGY_NONE;

  nghttp2_session_callbacks* callbacks
      = callback_struct_saved[hasGetPaddingCallback ? 1 : 0].callbacks;

  auto fn = type == NGHTTP2_SESSION_SERVER ?
      nghttp2_session_server_new3 :
      nghttp2_session_client_new3;

  MemoryAllocatorInfo allocator_info(this);

  
  
  
  
  
  CHECK_EQ(fn(&session_, callbacks, this, *opts, *allocator_info), 0);

  outgoing_storage_.reserve(1024);
  outgoing_buffers_.reserve(32);

  {
    
    Local<ArrayBuffer> ab =
        ArrayBuffer::New(env->isolate(), js_fields_, kSessionUint8FieldCount);
    Local<Uint8Array> uint8_arr =
        Uint8Array::New(ab, 0, kSessionUint8FieldCount);
    USE(wrap->Set(env->context(), env->fields_string(), uint8_arr));
  }
}