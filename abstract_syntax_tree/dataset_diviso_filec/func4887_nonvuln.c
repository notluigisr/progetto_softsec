void Scan::OptimizeDCTBlock(LONG bx,LONG by,UBYTE compidx,DOUBLE lambda,
                            class DCT *dct,LONG quantized[64])
{
  UBYTE i;

  assert(m_pParser);

  for(i = 0;i < m_ucCount;i++) {
    if (m_pComponent[i] && m_pComponent[i]->IndexOf() == compidx) {
      m_pParser->OptimizeBlock(bx,by,i,lambda,dct,quantized);
      break;
    }
  }
}