dir_server_t *
trusted_dir_server_new(const char *nickname, const char *address,
                       uint16_t dir_port, uint16_t or_port,
                       const tor_addr_port_t *ipv6_addrport,
                       const char *digest, const char *v3_auth_digest,
                       dirinfo_type_t type, double weight)
{
  uint32_t a;
  tor_addr_t addr;
  char *hostname=NULL;
  dir_server_t *result;

  if (!address) { 
    if (resolve_my_address(LOG_WARN, get_options(),
                           &a, NULL, &hostname) < 0) {
      log_warn(LD_CONFIG,
               "STR"
               "STR");
      return NULL;
    }
    if (!hostname)
      hostname = tor_dup_ip(a);
  } else {
    if (tor_lookup_hostname(address, &a)) {
      log_warn(LD_CONFIG,
               "STR",
               address);
      return NULL;
    }
    hostname = tor_strdup(address);
  }
  tor_addr_from_ipv4h(&addr, a);

  result = dir_server_new(1, nickname, &addr, hostname,
                          dir_port, or_port,
                          ipv6_addrport,
                          digest,
                          v3_auth_digest, type, weight);
  tor_free(hostname);
  return result;