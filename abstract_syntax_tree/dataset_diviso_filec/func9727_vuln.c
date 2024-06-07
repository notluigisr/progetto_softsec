  bool EmitWithSender(base::StringPiece name,
                      content::RenderFrameHost* sender,
                      electron::mojom::ElectronBrowser::InvokeCallback callback,
                      Args&&... args) {
    DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
    v8::Isolate* isolate = JavascriptEnvironment::GetIsolate();
    v8::HandleScope handle_scope(isolate);
    v8::Local<v8::Object> wrapper;
    if (!GetWrapper(isolate).ToLocal(&wrapper))
      return false;
    v8::Local<v8::Object> event = gin_helper::internal::CreateNativeEvent(
        isolate, wrapper, sender, std::move(callback));
    return EmitCustomEvent(name, event, std::forward<Args>(args)...);
  }