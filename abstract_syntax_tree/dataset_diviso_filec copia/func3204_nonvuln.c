static int csnmp_config_add_host_priv_protocol(host_definition_t *hd,
                                               oconfig_item_t *ci) {
  char buffer[4];
  int status;

  status = cf_util_get_string_buffer(ci, buffer, sizeof(buffer));
  if (status != 0)
    return status;

  if (strcasecmp("STR", buffer) == 0) {
    hd->priv_protocol = usmAESPrivProtocol;
    hd->priv_protocol_len = sizeof(usmAESPrivProtocol) / sizeof(oid);
  } else if (strcasecmp("STR", buffer) == 0) {
    hd->priv_protocol = usmDESPrivProtocol;
    hd->priv_protocol_len = sizeof(usmDESPrivProtocol) / sizeof(oid);
  } else {
    WARNING("STR"
            "STR");
    return (-1);
  }

  DEBUG("STR", hd->name,
        hd->priv_protocol == usmAESPrivProtocol ? "STR");

  return (0);
} 