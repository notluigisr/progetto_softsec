int dbd_db_login(SV* dbh, imp_dbh_t* imp_dbh, char* dbname, char* user,
		 char* password) {
#ifdef dTHR
  dTHR;
#endif
  dTHX; 
  D_imp_xxh(dbh);

  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh),
		  "STR",
		  dbname ? dbname : "STR",
		  user ? user : "STR",
		  password ? password : "STR");

  imp_dbh->stats.auto_reconnects_ok= 0;
  imp_dbh->stats.auto_reconnects_failed= 0;
  imp_dbh->bind_type_guessing= FALSE;
  imp_dbh->bind_comment_placeholders= FALSE;
  imp_dbh->has_transactions= TRUE;
 
  imp_dbh->auto_reconnect = FALSE;

  
#if defined(sv_utf8_decode) && MYSQL_VERSION_ID >=SERVER_PREPARE_VERSION
  imp_dbh->enable_utf8 = FALSE;  
#endif

  if (!my_login(aTHX_ dbh, imp_dbh))
  {
    do_error(dbh, mysql_errno(imp_dbh->pmysql),
            mysql_error(imp_dbh->pmysql) ,mysql_sqlstate(imp_dbh->pmysql));
    return FALSE;
  }

    
    DBIc_ACTIVE_on(imp_dbh);

    
    DBIc_on(imp_dbh, DBIcf_IMPSET);

    return TRUE;
}