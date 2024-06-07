static int fts3EvalPhraseStart(Fts3Cursor *pCsr, int bOptOk, Fts3Phrase *p){
  Fts3Table *pTab = (Fts3Table *)pCsr->base.pVtab;
  int rc = SQLITE_OK;             
  int i;

  
  int bHaveIncr = 0;
  int bIncrOk = (bOptOk 
   && pCsr->bDesc==pTab->bDescIdx 
   && p->nToken<=MAX_INCR_PHRASE_TOKENS && p->nToken>0
#ifdef SQLITE_TEST
   && pTab->bNoIncrDoclist==0
#endif
  );
  for(i=0; bIncrOk==1 && i<p->nToken; i++){
    Fts3PhraseToken *pToken = &p->aToken[i];
    if( pToken->bFirst || (pToken->pSegcsr!=0 && !pToken->pSegcsr->bLookup) ){
      bIncrOk = 0;
    }
    if( pToken->pSegcsr ) bHaveIncr = 1;
  }

  if( bIncrOk && bHaveIncr ){
    
    int iCol = (p->iColumn >= pTab->nColumn ? -1 : p->iColumn);
    for(i=0; rc==SQLITE_OK && i<p->nToken; i++){
      Fts3PhraseToken *pToken = &p->aToken[i];
      Fts3MultiSegReader *pSegcsr = pToken->pSegcsr;
      if( pSegcsr ){
        rc = sqlite3Fts3MsrIncrStart(pTab, pSegcsr, iCol, pToken->z, pToken->n);
      }
    }
    p->bIncr = 1;
  }else{
    
    rc = fts3EvalPhraseLoad(pCsr, p);
    p->bIncr = 0;
  }

  assert( rc!=SQLITE_OK || p->nToken<1 || p->aToken[0].pSegcsr==0 || p->bIncr );
  return rc;
}