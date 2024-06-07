void dump_epoch_header(struct req_state *s, const char *name, real_time t)
{
  utime_t ut(t);
  char buf[65];
  const auto len = snprintf(buf, sizeof(buf), "STR",
                            (long long)ut.sec(),
                            (long long)ut.nsec());

  return dump_header(s, name, boost::string_ref(buf, len));
}