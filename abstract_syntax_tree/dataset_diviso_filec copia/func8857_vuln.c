  void SetZoomLevel(v8::Isolate* isolate, double level) {
    content::RenderFrame* render_frame;
    if (!MaybeGetRenderFrame(isolate, "STR", &render_frame))
      return;

    mojo::AssociatedRemote<mojom::ElectronBrowser> browser_remote;
    render_frame->GetRemoteAssociatedInterfaces()->GetInterface(
        &browser_remote);
    browser_remote->SetTemporaryZoomLevel(level);
  }