content::WebContents* WebContents::OpenURLFromTab(
    content::WebContents* source,
    const content::OpenURLParams& params) {
  if (params.disposition != WindowOpenDisposition::CURRENT_TAB) {
    Emit("STR", params.referrer,
         params.post_data);
    return nullptr;
  }

  
  if (Emit("STR", params.url))
    return nullptr;

  
  
  if (IsDestroyed())
    return nullptr;

  return CommonWebContentsDelegate::OpenURLFromTab(source, params);
}