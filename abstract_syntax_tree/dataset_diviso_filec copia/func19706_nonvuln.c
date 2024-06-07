load_policy_from_option(config_line_t *config, const char *option_name,
                        smartlist_t **policy,
                        int assume_action)
{
  int r;
  int killed_any_ports = 0;
  addr_policy_list_free(*policy);
  *policy = NULL;
  r = parse_addr_policy(config, policy, assume_action);
  if (r < 0) {
    return -1;
  }
  if (*policy) {
    SMARTLIST_FOREACH_BEGIN(*policy, addr_policy_t *, n) {
      
      if (n->prt_min > 1 || n->prt_max != 65535) {
        addr_policy_t newp, *c;
        memcpy(&newp, n, sizeof(newp));
        newp.prt_min = 1;
        newp.prt_max = 65535;
        newp.is_canonical = 0;
        c = addr_policy_get_canonical_entry(&newp);
        SMARTLIST_REPLACE_CURRENT(*policy, n, c);
        addr_policy_free(n);
        killed_any_ports = 1;
      }
    } SMARTLIST_FOREACH_END(n);
  }
  if (killed_any_ports) {
    log_warn(LD_CONFIG, "STR", option_name);
  }
  return 0;
}