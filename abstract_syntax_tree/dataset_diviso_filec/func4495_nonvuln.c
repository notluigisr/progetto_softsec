void WebContents::UpdateTargetURL(content::WebContents* source,
                                  const GURL& url) {
  Emit("STR", url);
}