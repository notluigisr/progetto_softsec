void WebContents::MessageHost(const std::string& channel,
                              blink::CloneableMessage arguments,
                              content::RenderFrameHost* render_frame_host) {
  TRACE_EVENT1("STR", channel);
  
  EmitWithSender("STR", render_frame_host,
                 electron::mojom::ElectronBrowser::InvokeCallback(), channel,
                 std::move(arguments));
}