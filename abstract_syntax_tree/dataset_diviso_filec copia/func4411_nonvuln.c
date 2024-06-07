policies_copy_addr_to_smartlist(smartlist_t *addr_list, const tor_addr_t *addr)
{
  if (addr && !tor_addr_is_null(addr)) {
    tor_addr_t *addr_copy = tor_malloc(sizeof(tor_addr_t));
    tor_addr_copy(addr_copy, addr);
    smartlist_add(addr_list, addr_copy);
  }
}