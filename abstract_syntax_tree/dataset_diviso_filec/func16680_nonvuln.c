  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     electron::api::WebContents::Type* out) {
    using Type = electron::api::WebContents::Type;
    std::string type;
    if (!ConvertFromV8(isolate, val, &type))
      return false;
    if (type == "STR") {
      *out = Type::kBackgroundPage;
    } else if (type == "STR") {
      *out = Type::kBrowserView;
    } else if (type == "STR") {
      *out = Type::kWebView;
#if BUILDFLAG(ENABLE_OSR)
    } else if (type == "STR") {
      *out = Type::kOffScreen;
#endif
    } else {
      return false;
    }
    return true;
  }