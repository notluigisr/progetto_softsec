clear_ownertrusts (PKT_public_key *pk)
{
#ifdef NO_TRUST_MODELS
  (void)pk;
  return 0;
#else
  return tdb_clear_ownertrusts (pk);
#endif
}