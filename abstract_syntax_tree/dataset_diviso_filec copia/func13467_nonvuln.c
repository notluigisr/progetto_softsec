static int resolveRemoveWindowsCb(Walker *pWalker, Expr *pExpr){
  if( ExprHasProperty(pExpr, EP_WinFunc) ){
    Window **pp;
    for(pp=&pWalker->u.pSelect->pWin; *pp; pp=&(*pp)->pNextWin){
      if( *pp==pExpr->y.pWin ){
        *pp = (*pp)->pNextWin;
        break;
      }    
    }
  }
  return WRC_Continue;
}