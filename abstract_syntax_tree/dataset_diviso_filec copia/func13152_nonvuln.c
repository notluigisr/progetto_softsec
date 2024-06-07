static int check_certificate_expiration (X509 *peercert, int silent)
{
  if (option (OPTSSLVERIFYDATES) != MUTT_NO)
  {
    if (X509_cmp_current_time (X509_get0_notBefore (peercert)) >= 0)
    {
      if (!silent)
      {
        dprint (2, (debugfile, "STR"));
        mutt_error (_("STR"));
        mutt_sleep (2);
      }
      return 0;
    }
    if (X509_cmp_current_time (X509_get0_notAfter (peercert)) <= 0)
    {
      if (!silent)
      {
        dprint (2, (debugfile, "STR"));
        mutt_error (_("STR"));
        mutt_sleep (2);
      }
      return 0;
    }
  }

  return 1;
}