  v8::Local<v8::Value> GetFrameParent(v8::Isolate* isolate) {
    content::RenderFrame* render_frame;
    if (!MaybeGetRenderFrame(isolate, "STR", &render_frame))
      return v8::Null(isolate);

    blink::WebFrame* frame = render_frame->GetWebFrame()->Parent();
    return CreateWebFrameRenderer(isolate, frame);
  }