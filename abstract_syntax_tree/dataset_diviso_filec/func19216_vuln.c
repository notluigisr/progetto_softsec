bgp_attr_flags_diagnose
(
  struct peer * peer,
  const u_int8_t attr_code,
  u_int8_t desired_flags, 
  u_int8_t real_flags     
)
{
  u_char seen = 0, i;

  desired_flags &= ~BGP_ATTR_FLAG_EXTLEN;
  real_flags &= ~BGP_ATTR_FLAG_EXTLEN;
  for (i = 0; i <= 2; i++) 
    if
    (
      CHECK_FLAG (desired_flags, attr_flag_str[i].key) !=
      CHECK_FLAG (real_flags,    attr_flag_str[i].key)
    )
    {
      zlog (peer->log, LOG_ERR, "STR",
            LOOKUP (attr_str, attr_code),
            CHECK_FLAG (desired_flags, attr_flag_str[i].key) ? "STR",
            attr_flag_str[i].str);
      seen = 1;
    }
  assert (seen);
}