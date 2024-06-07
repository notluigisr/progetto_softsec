  v8::Local<v8::Value> SendSync(v8::Isolate* isolate,
                                gin_helper::ErrorThrower thrower,
                                bool internal,
                                const std::string& channel,
                                v8::Local<v8::Value> arguments) {
    if (!electron_browser_remote_) {
      thrower.ThrowError(kIPCMethodCalledAfterContextReleasedError);
      return v8::Local<v8::Value>();
    }
    blink::CloneableMessage message;
    if (!electron::SerializeV8Value(isolate, arguments, &message)) {
      return v8::Local<v8::Value>();
    }

    blink::CloneableMessage result;
    electron_browser_remote_->MessageSync(internal, channel, std::move(message),
                                          &result);
    return electron::DeserializeV8Value(isolate, result);
  }