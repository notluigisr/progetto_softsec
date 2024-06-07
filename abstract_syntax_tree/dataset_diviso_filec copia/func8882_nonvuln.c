int sqlite3ExprCodeGetColumn(
  Parse *pParse,   
  Table *pTab,     
  int iColumn,     
  int iTable,      
  int iReg,        
  u8 p5            
){
  assert( pParse->pVdbe!=0 );
  sqlite3ExprCodeGetColumnOfTable(pParse->pVdbe, pTab, iTable, iColumn, iReg);
  if( p5 ){
    sqlite3VdbeChangeP5(pParse->pVdbe, p5);
  }
  return iReg;
}