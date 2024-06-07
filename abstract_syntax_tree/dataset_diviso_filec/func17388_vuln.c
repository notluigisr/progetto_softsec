static int fts3SpecialInsert(Fts3Table *p, sqlite3_value *pVal){
  int rc;                         
  const char *zVal = (const char *)sqlite3_value_text(pVal);
  int nVal = sqlite3_value_bytes(pVal);

  if( !zVal ){
    return SQLITE_NOMEM;
  }else if( nVal==8 && 0==sqlite3_strnicmp(zVal, "STR", 8) ){
    rc = fts3DoOptimize(p, 0);
  }else if( nVal==7 && 0==sqlite3_strnicmp(zVal, "STR", 7) ){
    rc = fts3DoRebuild(p);
  }else if( nVal==15 && 0==sqlite3_strnicmp(zVal, "STR", 15) ){
    rc = fts3DoIntegrityCheck(p);
  }else if( nVal>6 && 0==sqlite3_strnicmp(zVal, "STR", 6) ){
    rc = fts3DoIncrmerge(p, &zVal[6]);
  }else if( nVal>10 && 0==sqlite3_strnicmp(zVal, "STR", 10) ){
    rc = fts3DoAutoincrmerge(p, &zVal[10]);
#ifdef SQLITE_TEST
  }else if( nVal>9 && 0==sqlite3_strnicmp(zVal, "STR", 9) ){
    p->nNodeSize = atoi(&zVal[9]);
    rc = SQLITE_OK;
  }else if( nVal>11 && 0==sqlite3_strnicmp(zVal, "STR", 9) ){
    p->nMaxPendingData = atoi(&zVal[11]);
    rc = SQLITE_OK;
  }else if( nVal>21 && 0==sqlite3_strnicmp(zVal, "STR", 21) ){
    p->bNoIncrDoclist = atoi(&zVal[21]);
    rc = SQLITE_OK;
#endif
  }else{
    rc = SQLITE_ERROR;
  }

  return rc;
}