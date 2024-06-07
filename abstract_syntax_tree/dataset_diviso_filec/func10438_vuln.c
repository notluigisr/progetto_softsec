  explicit IPCRenderer(v8::Isolate* isolate)
      : content::RenderFrameObserver(GetCurrentRenderFrame()) {
    RenderFrame* render_frame = GetCurrentRenderFrame();
    DCHECK(render_frame);
    weak_context_ =
        v8::Global<v8::Context>(isolate, isolate->GetCurrentContext());
    weak_context_.SetWeak();

    render_frame->GetBrowserInterfaceBroker()->GetInterface(
        electron_browser_remote_.BindNewPipeAndPassReceiver());
  }