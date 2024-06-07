goa_exchange_provider_class_init (GoaExchangeProviderClass *klass)
{
  GoaProviderClass *provider_class;

  provider_class = GOA_PROVIDER_CLASS (klass);
  provider_class->get_provider_type          = get_provider_type;
  provider_class->get_provider_name          = get_provider_name;
  provider_class->get_provider_group         = get_provider_group;
  provider_class->add_account                = add_account;
  provider_class->refresh_account            = refresh_account;
  provider_class->build_object               = build_object;
  provider_class->show_account               = show_account;
  provider_class->ensure_credentials_sync    = ensure_credentials_sync;
}