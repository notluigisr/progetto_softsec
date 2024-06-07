addr_is_in_cc_list(uint32_t addr, const smartlist_t *cc_list)
{
  country_t country;
  const char *name;
  tor_addr_t tar;

  if (!cc_list)
    return 0;
  
  tor_addr_from_ipv4h(&tar, addr);
  country = geoip_get_country_by_addr(&tar);
  name = geoip_get_country_name(country);
  return smartlist_contains_string_case(cc_list, name);
}