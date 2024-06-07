int sqlite3WhereOrderByLimitOptLabel(WhereInfo *pWInfo){
  WhereLevel *pInner;
  if( !pWInfo->bOrderedInnerLoop ){
    
    return pWInfo->iContinue;
  }
  pInner = &pWInfo->a[pWInfo->nLevel-1];
  assert( pInner->addrNxt!=0 );
  return pInner->pRJ ? pWInfo->iContinue : pInner->addrNxt;
}