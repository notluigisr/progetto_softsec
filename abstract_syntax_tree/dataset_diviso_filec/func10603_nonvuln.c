static int fts3IncrmergeOutputIdx( 
  Fts3Table *p,                   
  sqlite3_int64 iAbsLevel,        
  int *piIdx                      
){
  int rc;
  sqlite3_stmt *pOutputIdx = 0;   

  rc = fts3SqlStmt(p, SQL_NEXT_SEGMENT_INDEX, &pOutputIdx, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_int64(pOutputIdx, 1, iAbsLevel+1);
    sqlite3_step(pOutputIdx);
    *piIdx = sqlite3_column_int(pOutputIdx, 0);
    rc = sqlite3_reset(pOutputIdx);
  }

  return rc;
}