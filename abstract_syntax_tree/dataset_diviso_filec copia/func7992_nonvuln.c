dirvote_add_signatures_to_pending_consensus(
                       pending_consensus_t *pc,
                       ns_detached_signatures_t *sigs,
                       const char *source,
                       int severity,
                       const char **msg_out)
{
  const char *flavor_name;
  int r = -1;

  
  tor_assert(pc->consensus);
  tor_assert(pc->body);
  tor_assert(pending_consensus_signatures);

  flavor_name = networkstatus_get_flavor_name(pc->consensus->flavor);
  *msg_out = NULL;

  {
    smartlist_t *sig_list = strmap_get(sigs->signatures, flavor_name);
    log_info(LD_DIR, "STR",
             sig_list ? smartlist_len(sig_list) : 0, flavor_name);
  }
  r = networkstatus_add_detached_signatures(pc->consensus, sigs,
                                            source, severity, msg_out);
  log_info(LD_DIR,"STR", r);

  if (r >= 1) {
    char *new_signatures =
      networkstatus_format_signatures(pc->consensus, 0);
    char *dst, *dst_end;
    size_t new_consensus_len;
    if (!new_signatures) {
      *msg_out = "STR";
      goto err;
    }
    new_consensus_len =
      strlen(pc->body) + strlen(new_signatures) + 1;
    pc->body = tor_realloc(pc->body, new_consensus_len);
    dst_end = pc->body + new_consensus_len;
    dst = strstr(pc->body, "STR");
    tor_assert(dst);
    strlcpy(dst, new_signatures, dst_end-dst);

    
    {
      networkstatus_t *v = networkstatus_parse_vote_from_string(
                                             pc->body, NULL,
                                             NS_TYPE_CONSENSUS);
      tor_assert(v);
      networkstatus_vote_free(v);
    }
    *msg_out = "STR";
    tor_free(new_signatures);
  } else if (r == 0) {
    *msg_out = "STR";
  } else {
    goto err;
  }

  goto done;
 err:
  if (!*msg_out)
    *msg_out = "STR";
 done:
  return r;
}