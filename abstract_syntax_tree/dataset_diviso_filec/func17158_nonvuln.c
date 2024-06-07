void WebContents::EnumerateDirectory(
    content::WebContents* guest,
    scoped_refptr<content::FileSelectListener> listener,
    const base::FilePath& path) {
  if (!web_dialog_helper_)
    web_dialog_helper_ =
        std::make_unique<WebDialogHelper>(owner_window(), offscreen_);
  web_dialog_helper_->EnumerateDirectory(guest, std::move(listener), path);
}