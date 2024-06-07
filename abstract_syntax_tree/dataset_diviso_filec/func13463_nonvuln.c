void WebContents::RunFileChooser(
    content::RenderFrameHost* render_frame_host,
    scoped_refptr<content::FileSelectListener> listener,
    const blink::mojom::FileChooserParams& params) {
  if (!web_dialog_helper_)
    web_dialog_helper_ =
        std::make_unique<WebDialogHelper>(owner_window(), offscreen_);
  web_dialog_helper_->RunFileChooser(render_frame_host, std::move(listener),
                                     params);
}