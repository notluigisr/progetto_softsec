void ElectronBrowserClient::RegisterNonNetworkSubresourceURLLoaderFactories(
    int render_process_id,
    int render_frame_id,
    const absl::optional<url::Origin>& request_initiator_origin,
    NonNetworkURLLoaderFactoryMap* factories) {
  auto* render_process_host =
      content::RenderProcessHost::FromID(render_process_id);
  DCHECK(render_process_host);
  if (!render_process_host || !render_process_host->GetBrowserContext())
    return;

  content::RenderFrameHost* frame_host =
      content::RenderFrameHost::FromID(render_process_id, render_frame_id);
  content::WebContents* web_contents =
      content::WebContents::FromRenderFrameHost(frame_host);

  
  
  bool allow_file_access = false;
  if (web_contents) {
    const auto& web_preferences = web_contents->GetOrCreateWebPreferences();
    if (!web_preferences.web_security_enabled)
      allow_file_access = true;
  }

  ProtocolRegistry::FromBrowserContext(render_process_host->GetBrowserContext())
      ->RegisterURLLoaderFactories(factories, allow_file_access);

#if BUILDFLAG(ENABLE_ELECTRON_EXTENSIONS)
  auto factory = extensions::CreateExtensionURLLoaderFactory(render_process_id,
                                                             render_frame_id);
  if (factory)
    factories->emplace(extensions::kExtensionScheme, std::move(factory));

  if (!web_contents)
    return;

  extensions::ElectronExtensionWebContentsObserver* web_observer =
      extensions::ElectronExtensionWebContentsObserver::FromWebContents(
          web_contents);

  
  
  if (!web_observer)
    return;

  const extensions::Extension* extension =
      web_observer->GetExtensionFromFrame(frame_host, false);
  if (!extension)
    return;

  
  if (extension->is_extension() &&
      extensions::Manifest::IsComponentLocation(extension->location())) {
    
    
    factories->emplace(content::kChromeUIScheme,
                       content::CreateWebUIURLLoaderFactory(
                           frame_host, content::kChromeUIScheme,
                           {content::kChromeUIResourcesHost}));
  }

  
  
  
  extensions::Manifest::Type type = extension->GetType();
  if (type == extensions::Manifest::TYPE_EXTENSION &&
      AllowFileAccess(extension->id(), web_contents->GetBrowserContext())) {
    factories->emplace(url::kFileScheme,
                       FileURLLoaderFactory::Create(render_process_id));
  }
#endif
}