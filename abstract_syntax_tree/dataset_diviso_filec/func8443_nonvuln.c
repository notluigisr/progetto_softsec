gin::Handle<WebContents> WebContents::New(
    v8::Isolate* isolate,
    const gin_helper::Dictionary& options) {
  gin::Handle<WebContents> handle =
      gin::CreateHandle(isolate, new WebContents(isolate, options));
  gin_helper::CallMethod(isolate, handle.get(), "STR");
  return handle;
}