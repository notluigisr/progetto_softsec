  void SendTo(v8::Isolate* isolate,
              gin_helper::ErrorThrower thrower,
              int32_t web_contents_id,
              const std::string& channel,
              v8::Local<v8::Value> arguments) {
    if (!electron_browser_remote_) {
      thrower.ThrowError(kIPCMethodCalledAfterContextReleasedError);
      return;
    }
    blink::CloneableMessage message;
    if (!electron::SerializeV8Value(isolate, arguments, &message)) {
      return;
    }
    electron_browser_remote_->MessageTo(web_contents_id, channel,
                                        std::move(message));
  }