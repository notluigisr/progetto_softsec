  double GetZoomLevel(v8::Isolate* isolate) {
    double result = 0.0;
    content::RenderFrame* render_frame;
    if (!MaybeGetRenderFrame(isolate, "STR", &render_frame))
      return result;

    mojo::Remote<mojom::ElectronBrowser> browser_remote;
    render_frame->GetBrowserInterfaceBroker()->GetInterface(
        browser_remote.BindNewPipeAndPassReceiver());
    browser_remote->DoGetZoomLevel(&result);
    return result;
  }