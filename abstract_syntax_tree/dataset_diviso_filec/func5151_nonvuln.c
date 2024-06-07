void Http2Stream::RespondFD(const FunctionCallbackInfo<Value>& args) {
  Environment* env = Environment::GetCurrent(args);
  Local<Context> context = env->context();
  Isolate* isolate = env->isolate();
  Http2Stream* stream;
  ASSIGN_OR_RETURN_UNWRAP(&stream, args.Holder());

  int fd = args[0]->Int32Value(context).ToChecked();
  Local<Array> headers = args[1].As<Array>();

  int64_t offset = args[2]->IntegerValue(context).ToChecked();
  int64_t length = args[3]->IntegerValue(context).ToChecked();
  int options = args[4]->IntegerValue(context).ToChecked();

  stream->session()->SetChunksSinceLastWrite();

  Headers list(isolate, context, headers);
  args.GetReturnValue().Set(stream->SubmitFile(fd, *list, list.length(),
                                               offset, length, options));
  DEBUG_HTTP2STREAM2(stream, "STR", fd);
}