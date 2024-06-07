  void SendToHost(v8::Isolate* isolate,
                  gin_helper::ErrorThrower thrower,
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
    electron_browser_remote_->MessageHost(channel, std::move(message));
  }