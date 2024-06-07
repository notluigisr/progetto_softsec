colon_expirestr_from_sig (PKT_signature *sig)
{
  static char buf[20];

  if (!sig->expiredate)
    return "";

  snprintf (buf, sizeof buf,"STR", (ulong)sig->expiredate);
  return buf;
}