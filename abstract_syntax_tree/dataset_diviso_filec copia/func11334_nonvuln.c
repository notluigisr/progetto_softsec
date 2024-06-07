static void fts3SqlExec(
  int *pRC,                
  Fts3Table *p,            
  int eStmt,               
  sqlite3_value **apVal    
){
  sqlite3_stmt *pStmt;
  int rc;
  if( *pRC ) return;
  rc = fts3SqlStmt(p, eStmt, &pStmt, apVal); 
  if( rc==SQLITE_OK ){
    sqlite3_step(pStmt);
    rc = sqlite3_reset(pStmt);
  }
  *pRC = rc;
}