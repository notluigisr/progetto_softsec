static int fts3AllocateSegdirIdx(
  Fts3Table *p, 
  int iLangid,                    
  int iIndex,                     
  int iLevel, 
  int *piIdx
){
  int rc;                         
  sqlite3_stmt *pNextIdx;         
  int iNext = 0;                  

  assert( iLangid>=0 );
  assert( p->nIndex>=1 );

  
  rc = fts3SqlStmt(p, SQL_NEXT_SEGMENT_INDEX, &pNextIdx, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_int64(
        pNextIdx, 1, getAbsoluteLevel(p, iLangid, iIndex, iLevel)
    );
    if( SQLITE_ROW==sqlite3_step(pNextIdx) ){
      iNext = sqlite3_column_int(pNextIdx, 0);
    }
    rc = sqlite3_reset(pNextIdx);
  }

  if( rc==SQLITE_OK ){
    
    if( iNext>=FTS3_MERGE_COUNT ){
      fts3LogMerge(16, getAbsoluteLevel(p, iLangid, iIndex, iLevel));
      rc = fts3SegmentMerge(p, iLangid, iIndex, iLevel);
      *piIdx = 0;
    }else{
      *piIdx = iNext;
    }
  }

  return rc;
}