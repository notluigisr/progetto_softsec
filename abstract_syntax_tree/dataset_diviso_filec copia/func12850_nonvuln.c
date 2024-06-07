mock_get_interface_address6_list(int severity,
                            sa_family_t family,
                            int include_internal)
{
  (void)severity;
  (void)include_internal;
  smartlist_t *clone_list = smartlist_new();
  smartlist_t *template_list = NULL;

  if (family == AF_INET) {
    template_list = mock_ipv4_addrs;
  } else if (family == AF_INET6) {
    template_list = mock_ipv6_addrs;
  } else {
    return NULL;
  }

  tt_assert(template_list);

  SMARTLIST_FOREACH_BEGIN(template_list, tor_addr_t *, src_addr) {
    tor_addr_t *dest_addr = tor_malloc(sizeof(tor_addr_t));
    memset(dest_addr, 0, sizeof(*dest_addr));
    tor_addr_copy_tight(dest_addr, src_addr);
    smartlist_add(clone_list, dest_addr);
  } SMARTLIST_FOREACH_END(src_addr);

  return clone_list;

 done:
  free_interface_address6_list(clone_list);
  return NULL;
}