void WebContents::DOMContentLoaded(
    content::RenderFrameHost* render_frame_host) {
  if (!render_frame_host->GetParent())
    Emit("STR");
}