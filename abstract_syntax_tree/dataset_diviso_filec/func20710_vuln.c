  void PostMessage(v8::Isolate* isolate,
                   gin_helper::ErrorThrower thrower,
                   const std::string& channel,
                   v8::Local<v8::Value> message_value,
                   absl::optional<v8::Local<v8::Value>> transfer) {
    if (!electron_browser_remote_) {
      thrower.ThrowError(kIPCMethodCalledAfterContextReleasedError);
      return;
    }
    blink::TransferableMessage transferable_message;
    if (!electron::SerializeV8Value(isolate, message_value,
                                    &transferable_message)) {
      
      return;
    }

    std::vector<v8::Local<v8::Object>> transferables;
    if (transfer && !transfer.value()->IsUndefined()) {
      if (!gin::ConvertFromV8(isolate, *transfer, &transferables)) {
        thrower.ThrowTypeError("STR");
        return;
      }
    }

    std::vector<blink::MessagePortChannel> ports;
    for (auto& transferable : transferables) {
      absl::optional<blink::MessagePortChannel> port =
          blink::WebMessagePortConverter::
              DisentangleAndExtractMessagePortChannel(isolate, transferable);
      if (!port.has_value()) {
        thrower.ThrowTypeError("STR");
        return;
      }
      ports.emplace_back(port.value());
    }

    transferable_message.ports = std::move(ports);
    electron_browser_remote_->ReceivePostMessage(
        channel, std::move(transferable_message));
  }