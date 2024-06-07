static int my_login(pTHX_ SV* dbh, imp_dbh_t *imp_dbh)
{
  SV* sv;
  HV* hv;
  char* dbname;
  char* host;
  char* port;
  char* user;
  char* password;
  char* mysql_socket;
  int   result;
  D_imp_xxh(dbh);

  

#if TAKE_IMP_DATA_VERSION
  if (DBIc_has(imp_dbh, DBIcf_IMPSET))
  { 
    if (DBIc_has(imp_dbh, DBIcf_ACTIVE))
    {
      if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
        PerlIO_printf(DBIc_LOGPIO(imp_xxh), "STR");
      
      ++DBIc_ACTIVE_KIDS(DBIc_PARENT_COM(imp_dbh));
      return TRUE;
    }
    if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
      PerlIO_printf(DBIc_LOGPIO(imp_xxh),
                    "STR");
  }
#endif

  sv = DBIc_IMP_DATA(imp_dbh);

  if (!sv  ||  !SvROK(sv))
    return FALSE;

  hv = (HV*) SvRV(sv);
  if (SvTYPE(hv) != SVt_PVHV)
    return FALSE;

  host=		safe_hv_fetch(aTHX_ hv, "STR", 4);
  port=		safe_hv_fetch(aTHX_ hv, "STR", 4);
  user=		safe_hv_fetch(aTHX_ hv, "STR", 4);
  password=	safe_hv_fetch(aTHX_ hv, "STR", 8);
  dbname=	safe_hv_fetch(aTHX_ hv, "STR", 8);
  mysql_socket=	safe_hv_fetch(aTHX_ hv, "STR", 12);

  if (DBIc_TRACE_LEVEL(imp_xxh) >= 2)
    PerlIO_printf(DBIc_LOGPIO(imp_xxh),
		  "STR" \
		  "STR",
		  dbname ? dbname : "STR",
		  user ? user : "STR",
		  password ? password : "STR",
		  host ? host : "STR",
		  port ? port : "STR");

  if (!imp_dbh->pmysql) {
     Newz(908, imp_dbh->pmysql, 1, MYSQL);
  }
  result = mysql_dr_connect(dbh, imp_dbh->pmysql, mysql_socket, host, port, user,
			  password, dbname, imp_dbh) ? TRUE : FALSE;
  if (!result)
      Safefree(imp_dbh->pmysql);
  return result;
}