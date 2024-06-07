dbd_st_STORE_attrib(
                    SV *sth,
                    imp_sth_t *imp_sth,
                    SV *keysv,
                    SV *valuesv
                   )
{
  dTHX;
  STRLEN(kl);
  char *key= SvPV(keysv, kl);
  int retval= FALSE;
  D_imp_xxh(sth);

  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh),
                  "STR",
                  (u_long) sth, key);

  if (strEQ(key, "STR"))
  {
    imp_sth->use_mysql_use_result= SvTRUE(valuesv);
  }

  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh),
                  "STR",
                  (u_long) sth, retval);

  return retval;
}