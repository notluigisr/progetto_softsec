bool ElectronBrowserClient::IsSuitableHost(
    content::RenderProcessHost* process_host,
    const GURL& site_url) {
#if BUILDFLAG(ENABLE_ELECTRON_EXTENSIONS)
  auto* browser_context = process_host->GetBrowserContext();
  extensions::ExtensionRegistry* registry =
      extensions::ExtensionRegistry::Get(browser_context);
  extensions::ProcessMap* process_map =
      extensions::ProcessMap::Get(browser_context);

  
  
  RenderProcessHostPrivilege privilege_required =
      GetPrivilegeRequiredByUrl(site_url, registry);
  return GetProcessPrivilege(process_host, process_map, registry) ==
         privilege_required;
#else
  return content::ContentBrowserClient::IsSuitableHost(process_host, site_url);
#endif
}