static char *fts3ReadExprList(Fts3Table *p, const char *zFunc, int *pRc){
  char *zRet = 0;
  char *zFree = 0;
  char *zFunction;
  int i;

  if( p->zContentTbl==0 ){
    if( !zFunc ){
      zFunction = "";
    }else{
      zFree = zFunction = fts3QuoteId(zFunc);
    }
    fts3Appendf(pRc, &zRet, "STR");
    for(i=0; i<p->nColumn; i++){
      fts3Appendf(pRc, &zRet, "STR", zFunction, i, p->azColumn[i]);
    }
    if( p->zLanguageid ){
      fts3Appendf(pRc, &zRet, "STR");
    }
    sqlite3_free(zFree);
  }else{
    fts3Appendf(pRc, &zRet, "STR");
    for(i=0; i<p->nColumn; i++){
      fts3Appendf(pRc, &zRet, "STR", p->azColumn[i]);
    }
    if( p->zLanguageid ){
      fts3Appendf(pRc, &zRet, "STR", p->zLanguageid);
    }
  }
  fts3Appendf(pRc, &zRet, "STR", 
      p->zDb,
      (p->zContentTbl ? p->zContentTbl : p->zName),
      (p->zContentTbl ? "STR")
  );
  return zRet;
}