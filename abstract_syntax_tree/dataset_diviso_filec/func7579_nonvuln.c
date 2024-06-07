  void Completed(
      const blink::WebVector<v8::Local<v8::Value>>& result) override {
    v8::Isolate* isolate = promise_.isolate();
    if (!result.empty()) {
      if (!result[0].IsEmpty()) {
        v8::Local<v8::Value> value = result[0];
        
        
        
        bool should_clone_value =
            !(value->IsObject() &&
              promise_.GetContext() ==
                  value.As<v8::Object>()->CreationContext()) &&
            value->IsObject();
        if (should_clone_value) {
          CopyResultToCallingContextAndFinalize(isolate,
                                                value.As<v8::Object>());
        } else {
          
          if (callback_)
            std::move(callback_).Run(value, v8::Undefined(isolate));
          promise_.Resolve(value);
        }
      } else {
        const char error_message[] =
            "STR"
            "STR";
        if (!callback_.is_null()) {
          v8::Local<v8::Context> context = promise_.GetContext();
          v8::Context::Scope context_scope(context);
          std::move(callback_).Run(
              v8::Undefined(isolate),
              v8::Exception::Error(
                  v8::String::NewFromUtf8(isolate, error_message)
                      .ToLocalChecked()));
        }
        promise_.RejectWithErrorMessage(error_message);
      }
    } else {
      const char error_message[] =
          "STR"
          "STR";
      if (!callback_.is_null()) {
        v8::Local<v8::Context> context = promise_.GetContext();
        v8::Context::Scope context_scope(context);
        std::move(callback_).Run(
            v8::Undefined(isolate),
            v8::Exception::Error(v8::String::NewFromUtf8(isolate, error_message)
                                     .ToLocalChecked()));
      }
      promise_.RejectWithErrorMessage(error_message);
    }
    delete this;
  }