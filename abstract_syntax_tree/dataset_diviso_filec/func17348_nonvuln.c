std::string WebContents::GetUserAgent() {
  return web_contents()->GetUserAgentOverride().ua_string_override;
}