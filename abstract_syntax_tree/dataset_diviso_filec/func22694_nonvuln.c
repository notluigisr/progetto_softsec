bool WebContents::IsGuest() const {
  return type_ == Type::kWebView;
}