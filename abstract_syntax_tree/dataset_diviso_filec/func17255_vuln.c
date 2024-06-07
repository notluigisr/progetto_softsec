  double GetZoomLevel(v8::Isolate* isolate) {
    double result = 0.0;
    content::RenderFrame* render_frame;
    if (!MaybeGetRenderFrame(isolate, "STR", &render_frame))
      return result;

    mojo::AssociatedRemote<mojom::ElectronBrowser> browser_remote;
    render_frame->GetRemoteAssociatedInterfaces()->GetInterface(
        &browser_remote);
    browser_remote->DoGetZoomLevel(&result);
    return result;
  }