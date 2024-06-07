PrefService* GetPrefService(content::WebContents* web_contents) {
  auto* context = web_contents->GetBrowserContext();
  return static_cast<electron::ElectronBrowserContext*>(context)->prefs();
}