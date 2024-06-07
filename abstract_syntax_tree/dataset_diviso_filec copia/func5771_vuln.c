  void SetZoomLevel(v8::Isolate* isolate, double level) {
    content::RenderFrame* render_frame;
    if (!MaybeGetRenderFrame(isolate, "STR", &render_frame))
      return;

    mojo::Remote<mojom::ElectronBrowser> browser_remote;
    render_frame->GetBrowserInterfaceBroker()->GetInterface(
        browser_remote.BindNewPipeAndPassReceiver());
    browser_remote->SetTemporaryZoomLevel(level);
  }