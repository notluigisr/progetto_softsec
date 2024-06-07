tdbio_read_model(void)
{
  TRUSTREC vr;
  int rc;

  rc = tdbio_read_record( 0, &vr, RECTYPE_VER );
  if( rc )
    log_fatal( _("STR"),
	       db_name, gpg_strerror (rc) );
  return vr.r.ver.trust_model;
}