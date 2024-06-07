void WebContents::Destroy() {
  
  
  if (Browser::Get()->is_shutting_down() || IsGuest()) {
    DeleteThisIfAlive();
  } else {
    base::PostTask(FROM_HERE, {content::BrowserThread::UI},
                   base::BindOnce(
                       [](base::WeakPtr<WebContents> contents) {
                         if (contents)
                           contents->DeleteThisIfAlive();
                       },
                       GetWeakPtr()));
  }
}