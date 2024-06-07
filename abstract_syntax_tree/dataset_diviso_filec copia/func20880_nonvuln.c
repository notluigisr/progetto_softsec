routerset_refresh_countries(routerset_t *target)
{
  int cc;
  bitarray_free(target->countries);

  if (!geoip_is_loaded()) {
    target->countries = NULL;
    target->n_countries = 0;
    return;
  }
  target->n_countries = geoip_get_n_countries();
  target->countries = bitarray_init_zero(target->n_countries);
  SMARTLIST_FOREACH_BEGIN(target->country_names, const char *, country) {
    cc = geoip_get_country(country);
    if (cc >= 0) {
      tor_assert(cc < target->n_countries);
      bitarray_set(target->countries, cc);
    } else {
      log(LOG_WARN, LD_CONFIG, "STR",
          country);
    }
  } SMARTLIST_FOREACH_END(country);
}