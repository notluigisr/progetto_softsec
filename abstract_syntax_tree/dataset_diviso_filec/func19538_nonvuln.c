short_policy_is_reject_star(const short_policy_t *policy)
{
  
  tor_assert(policy);
  
  return (policy->is_accept == 0 && policy->n_entries == 1 &&
          policy->entries[0].min_port == 1 &&
          policy->entries[0].max_port == 65535);
}