evdns_callback(int result, char type, int count, int ttl, void *addresses,
               void *arg)
{
  char *string_address = arg;
  uint8_t is_reverse = 0;
  int status = DNS_RESOLVE_FAILED_PERMANENT;
  uint32_t addr = 0;
  const char *hostname = NULL;
  int was_wildcarded = 0;

  if (result == DNS_ERR_NONE) {
    if (type == DNS_IPv4_A && count) {
      char answer_buf[INET_NTOA_BUF_LEN+1];
      struct in_addr in;
      char *escaped_address;
      uint32_t *addrs = addresses;
      in.s_addr = addrs[0];
      addr = ntohl(addrs[0]);
      status = DNS_RESOLVE_SUCCEEDED;
      tor_inet_ntoa(&in, answer_buf, sizeof(answer_buf));
      escaped_address = esc_for_log(string_address);

      if (answer_is_wildcarded(answer_buf)) {
        log_debug(LD_EXIT, "STR"
                  "STR",
                  safe_str(escaped_address),
                  escaped_safe_str(answer_buf));
        was_wildcarded = 1;
        addr = 0;
        status = DNS_RESOLVE_FAILED_PERMANENT;
      } else {
        log_debug(LD_EXIT, "STR",
                  safe_str(escaped_address),
                  escaped_safe_str(answer_buf));
      }
      tor_free(escaped_address);
    } else if (type == DNS_PTR && count) {
      char *escaped_address;
      is_reverse = 1;
      hostname = ((char**)addresses)[0];
      status = DNS_RESOLVE_SUCCEEDED;
      escaped_address = esc_for_log(string_address);
      log_debug(LD_EXIT, "STR",
                safe_str(escaped_address),
                escaped_safe_str(hostname));
      tor_free(escaped_address);
    } else if (count) {
      log_warn(LD_EXIT, "STR",
               escaped_safe_str(string_address));
    } else {
      log_warn(LD_BUG, "STR",
               escaped_safe_str(string_address));
    }
  } else {
    if (evdns_err_is_transient(result))
      status = DNS_RESOLVE_FAILED_TRANSIENT;
  }
  if (was_wildcarded) {
    if (is_test_address(string_address)) {
      
      add_wildcarded_test_address(string_address);
    }
  }
  if (result != DNS_ERR_SHUTDOWN)
    dns_found_answer(string_address, is_reverse, addr, hostname, status, ttl);
  tor_free(string_address);
}