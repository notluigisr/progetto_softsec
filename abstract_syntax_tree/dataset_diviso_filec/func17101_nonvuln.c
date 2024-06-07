set<string> Monitor::get_sync_targets_names()
{
  set<string> targets;
  targets.insert(paxos->get_name());
  for (int i = 0; i < PAXOS_NUM; ++i)
    paxos_service[i]->get_store_prefixes(targets);
  ConfigKeyService *config_key_service_ptr = dynamic_cast<ConfigKeyService*>(config_key_service);
  assert(config_key_service_ptr);
  config_key_service_ptr->get_store_prefixes(targets);
  return targets;
}