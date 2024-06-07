static int fts3DoIntegrityCheck(
  Fts3Table *p                    
){
  int rc;
  int bOk = 0;
  rc = fts3IntegrityCheck(p, &bOk);
  if( rc==SQLITE_OK && bOk==0 ) rc = FTS_CORRUPT_VTAB;
  return rc;
}