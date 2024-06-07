load_downloaded_routers(const char *body, smartlist_t *which,
                        int descriptor_digests,
                        int router_purpose,
                        const char *source)
{
  char buf[256];
  char time_buf[ISO_TIME_LEN+1];
  int added = 0;
  int general = router_purpose == ROUTER_PURPOSE_GENERAL;
  format_iso_time(time_buf, time(NULL));
  tor_assert(source);

  if (tor_snprintf(buf, sizeof(buf),
                   "STR"
                   "STR"
                   "STR", time_buf, escaped(source),
                   !general ? "STR",
                   !general ? router_purpose_to_string(router_purpose) : "",
                   !general ? "STR")<0)
    return added;

  added = router_load_routers_from_string(body, NULL, SAVED_NOWHERE, which,
                                  descriptor_digests, buf);
  control_event_bootstrap(BOOTSTRAP_STATUS_LOADING_DESCRIPTORS,
                          count_loading_descriptors_progress());
  return added;
}