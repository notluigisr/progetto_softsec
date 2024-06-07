void sqlite3UniqueConstraint(
  Parse *pParse,    
  int onError,      
  Index *pIdx       
){
  char *zErr;
  int j;
  StrAccum errMsg;
  Table *pTab = pIdx->pTable;

  sqlite3StrAccumInit(&errMsg, pParse->db, 0, 0, 
                      pParse->db->aLimit[SQLITE_LIMIT_LENGTH]);
  if( pIdx->aColExpr ){
    sqlite3_str_appendf(&errMsg, "STR", pIdx->zName);
  }else{
    for(j=0; j<pIdx->nKeyCol; j++){
      char *zCol;
      assert( pIdx->aiColumn[j]>=0 );
      zCol = pTab->aCol[pIdx->aiColumn[j]].zName;
      if( j ) sqlite3_str_append(&errMsg, "STR", 2);
      sqlite3_str_appendall(&errMsg, pTab->zName);
      sqlite3_str_append(&errMsg, "STR", 1);
      sqlite3_str_appendall(&errMsg, zCol);
    }
  }
  zErr = sqlite3StrAccumFinish(&errMsg);
  sqlite3HaltConstraint(pParse, 
    IsPrimaryKeyIndex(pIdx) ? SQLITE_CONSTRAINT_PRIMARYKEY 
                            : SQLITE_CONSTRAINT_UNIQUE,
    onError, zErr, P4_DYNAMIC, P5_ConstraintUnique);
}