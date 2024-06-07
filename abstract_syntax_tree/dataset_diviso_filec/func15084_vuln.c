  v8::Local<v8::Promise> Invoke(v8::Isolate* isolate,
                                gin_helper::ErrorThrower thrower,
                                bool internal,
                                const std::string& channel,
                                v8::Local<v8::Value> arguments) {
    if (!electron_browser_remote_) {
      thrower.ThrowError(kIPCMethodCalledAfterContextReleasedError);
      return v8::Local<v8::Promise>();
    }
    blink::CloneableMessage message;
    if (!electron::SerializeV8Value(isolate, arguments, &message)) {
      return v8::Local<v8::Promise>();
    }
    gin_helper::Promise<blink::CloneableMessage> p(isolate);
    auto handle = p.GetHandle();

    electron_browser_remote_->Invoke(
        internal, channel, std::move(message),
        base::BindOnce(
            [](gin_helper::Promise<blink::CloneableMessage> p,
               blink::CloneableMessage result) { p.Resolve(result); },
            std::move(p)));

    return handle;
  }