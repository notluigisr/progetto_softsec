void WebContents::Invoke(
    bool internal,
    const std::string& channel,
    blink::CloneableMessage arguments,
    electron::mojom::ElectronBrowser::InvokeCallback callback,
    content::RenderFrameHost* render_frame_host) {
  TRACE_EVENT1("STR", channel);
  
  EmitWithSender("STR", render_frame_host, std::move(callback),
                 internal, channel, std::move(arguments));
}