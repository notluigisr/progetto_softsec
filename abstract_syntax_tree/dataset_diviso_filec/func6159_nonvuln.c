void WebContents::HandleNewRenderFrame(
    content::RenderFrameHost* render_frame_host) {
  auto* rwhv = render_frame_host->GetView();
  if (!rwhv)
    return;

  
  auto* web_preferences = WebContentsPreferences::From(web_contents());
  if (web_preferences) {
    bool guest = IsGuest() || type_ == Type::kBrowserView;
    absl::optional<SkColor> color =
        guest ? SK_ColorTRANSPARENT : web_preferences->GetBackgroundColor();
    web_contents()->SetPageBaseBackgroundColor(color);
    SetBackgroundColor(rwhv, color.value_or(SK_ColorWHITE));
  }

  if (!background_throttling_)
    render_frame_host->GetRenderViewHost()->SetSchedulerThrottling(false);

  auto* rwh_impl =
      static_cast<content::RenderWidgetHostImpl*>(rwhv->GetRenderWidgetHost());
  if (rwh_impl)
    rwh_impl->disable_hidden_ = !background_throttling_;

  auto* web_frame = WebFrameMain::FromRenderFrameHost(render_frame_host);
  if (web_frame)
    web_frame->Connect();
}