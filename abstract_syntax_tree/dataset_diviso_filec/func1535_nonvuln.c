rend_service_del_ephemeral(const char *service_id)
{
  rend_service_t *s;
  if (!rend_valid_service_id(service_id)) {
    log_warn(LD_CONFIG, "STR");
    return -1;
  }
  if ((s = rend_service_get_by_service_id(service_id)) == NULL) {
    log_warn(LD_CONFIG, "STR"
             "STR");
    return -1;
  }
  if (!rend_service_is_ephemeral(s)) {
    log_warn(LD_CONFIG, "STR");
    return -1;
  }

  
  SMARTLIST_FOREACH_BEGIN(circuit_get_global_list(), circuit_t *, circ) {
    if (!circ->marked_for_close &&
        (circ->purpose == CIRCUIT_PURPOSE_S_ESTABLISH_INTRO ||
         circ->purpose == CIRCUIT_PURPOSE_S_INTRO)) {
      origin_circuit_t *oc = TO_ORIGIN_CIRCUIT(circ);
      tor_assert(oc->rend_data);
      if (!rend_circuit_pk_digest_eq(oc, (uint8_t *) s->pk_digest)) {
        continue;
      }
      log_debug(LD_REND, "STR",
                safe_str_client(extend_info_describe(
                                          oc->build_state->chosen_exit)),
                rend_data_get_address(oc->rend_data));
      circuit_mark_for_close(circ, END_CIRC_REASON_FINISHED);
    }
  } SMARTLIST_FOREACH_END(circ);
  smartlist_remove(rend_service_list, s);
  rend_service_free(s);

  log_debug(LD_CONFIG, "STR", service_id);

  return 0;
}