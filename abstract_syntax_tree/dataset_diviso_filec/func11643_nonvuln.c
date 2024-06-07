const extensions::Extension* GetEnabledExtensionFromEffectiveURL(
    content::BrowserContext* context,
    const GURL& effective_url) {
  if (!effective_url.SchemeIs(extensions::kExtensionScheme))
    return nullptr;

  extensions::ExtensionRegistry* registry =
      extensions::ExtensionRegistry::Get(context);
  if (!registry)
    return nullptr;

  return registry->enabled_extensions().GetByID(effective_url.host());
}