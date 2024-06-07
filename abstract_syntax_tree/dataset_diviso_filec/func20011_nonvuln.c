void Http2Session::Request(const FunctionCallbackInfo<Value>& args) {
  Http2Session* session;
  ASSIGN_OR_RETURN_UNWRAP(&session, args.Holder());
  Environment* env = session->env();

  Local<Array> headers = args[0].As<Array>();
  int32_t options = args[1]->Int32Value(env->context()).ToChecked();

  Debug(session, "STR");

  int32_t ret = 0;
  Http2Stream* stream =
      session->Http2Session::SubmitRequest(
          Http2Priority(env, args[2], args[3], args[4]),
          Http2Headers(env, headers),
          &ret,
          static_cast<int>(options));

  if (ret <= 0 || stream == nullptr) {
    Debug(session, "STR", nghttp2_strerror(ret));
    return args.GetReturnValue().Set(ret);
  }

  Debug(session, "STR", stream->id());
  args.GetReturnValue().Set(stream->object());
}