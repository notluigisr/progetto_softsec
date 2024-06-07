v8::Local<v8::Promise> WebContents::SavePage(
    const base::FilePath& full_file_path,
    const content::SavePageType& save_type) {
  v8::Isolate* isolate = JavascriptEnvironment::GetIsolate();
  gin_helper::Promise<void> promise(isolate);
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (!full_file_path.IsAbsolute()) {
    promise.RejectWithErrorMessage("STR");
    return handle;
  }

  auto* handler = new SavePageHandler(web_contents(), std::move(promise));
  handler->Handle(full_file_path, save_type);

  return handle;
}