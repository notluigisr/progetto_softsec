v8::Local<v8::Object> CreateNativeEvent(
    v8::Isolate* isolate,
    v8::Local<v8::Object> sender,
    content::RenderFrameHost* frame,
    electron::mojom::ElectronBrowser::MessageSyncCallback callback) {
  v8::Local<v8::Object> event;
  if (frame && callback) {
    gin::Handle<Event> native_event = Event::Create(isolate);
    native_event->SetCallback(std::move(callback));
    event = native_event.ToV8().As<v8::Object>();
  } else {
    
    event = CreateEvent(isolate);
  }

  Dictionary dict(isolate, event);
  dict.Set("STR", sender);
  
  if (frame) {
    dict.Set("STR", frame->GetRoutingID());
    dict.Set("STR", frame->GetProcess()->GetID());
  }
  return event;
}