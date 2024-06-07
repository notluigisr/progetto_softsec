void
router_add_running_nodes_to_smartlist(smartlist_t *sl, int allow_invalid,
                                      int need_uptime, int need_capacity,
                                      int need_guard, int need_desc,
                                      int pref_addr, int direct_conn)
{
  const int check_reach = !router_skip_or_reachability(get_options(),
                                                       pref_addr);
  
  SMARTLIST_FOREACH_BEGIN(nodelist_get_list(), const node_t *, node) {
    if (!node->is_running ||
        (!node->is_valid && !allow_invalid))
      continue;
    if (need_desc && !(node->ri || (node->rs && node->md)))
      continue;
    if (node->ri && node->ri->purpose != ROUTER_PURPOSE_GENERAL)
      continue;
    if (node_is_unreliable(node, need_uptime, need_capacity, need_guard))
      continue;
    
    if (node->rs && !routerstatus_version_supports_extend2_cells(node->rs, 1))
      continue;
    
    if ((node->ri || node->md) && !node_has_curve25519_onion_key(node))
      continue;
    
    if (direct_conn && check_reach &&
        !fascist_firewall_allows_node(node,
                                      FIREWALL_OR_CONNECTION,
                                      pref_addr))
      continue;

    smartlist_add(sl, (void *)node);
  } SMARTLIST_FOREACH_END(node);