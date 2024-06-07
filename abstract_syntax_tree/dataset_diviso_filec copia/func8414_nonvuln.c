static void addWhereTerm(
  Parse *pParse,                  
  SrcList *pSrc,                  
  int iLeft,                      
  int iColLeft,                   
  int iRight,                     
  int iColRight,                  
  int isOuterJoin,                
  Expr **ppWhere                  
){
  sqlite3 *db = pParse->db;
  Expr *pE1;
  Expr *pE2;
  Expr *pEq;

  assert( iLeft<iRight );
  assert( pSrc->nSrc>iRight );
  assert( pSrc->a[iLeft].pTab );
  assert( pSrc->a[iRight].pTab );

  pE1 = sqlite3CreateColumnExpr(db, pSrc, iLeft, iColLeft);
  pE2 = sqlite3CreateColumnExpr(db, pSrc, iRight, iColRight);

  pEq = sqlite3PExpr(pParse, TK_EQ, pE1, pE2);
  if( pEq && isOuterJoin ){
    ExprSetProperty(pEq, EP_FromJoin);
    assert( !ExprHasProperty(pEq, EP_TokenOnly|EP_Reduced) );
    ExprSetVVAProperty(pEq, EP_NoReduce);
    pEq->iRightJoinTable = (i16)pE2->iTable;
  }
  *ppWhere = sqlite3ExprAnd(pParse, *ppWhere, pEq);
}