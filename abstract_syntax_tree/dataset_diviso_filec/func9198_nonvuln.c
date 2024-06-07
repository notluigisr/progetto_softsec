static void renameTokenFind(Parse *pParse, struct RenameCtx *pCtx, void *pPtr){
  RenameToken **pp;
  assert( pPtr!=0 );
  for(pp=&pParse->pRename; (*pp); pp=&(*pp)->pNext){
    if( (*pp)->p==pPtr ){
      RenameToken *pToken = *pp;
      *pp = pToken->pNext;
      pToken->pNext = pCtx->pList;
      pCtx->pList = pToken;
      pCtx->nList++;
      break;
    }
  }
}