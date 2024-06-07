int dbd_db_disconnect(SV* dbh, imp_dbh_t* imp_dbh)
{
#ifdef dTHR
  dTHR;
#endif
  dTHX;
  D_imp_xxh(dbh);

  
  
  DBIc_ACTIVE_off(imp_dbh);
  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh), "STR",
		              imp_dbh->pmysql);
  mysql_close(imp_dbh->pmysql );

  
  
  return TRUE;
}