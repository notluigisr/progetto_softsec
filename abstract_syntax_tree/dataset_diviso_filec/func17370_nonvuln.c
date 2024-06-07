void Http2Stream::RstStream(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  Local<Context> context = env->context();
  Http2Stream* stream;
  ASSIGN_OR_RETURN_UNWRAP(&stream, args.Holder());
  uint32_t code = args[0]->Uint32Value(context).ToChecked();
  DEBUG_HTTP2STREAM2(stream, "STR", code);
  stream->SubmitRstStream(code);
}