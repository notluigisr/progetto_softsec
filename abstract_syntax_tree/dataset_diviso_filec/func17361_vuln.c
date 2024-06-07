void LosslessScan::ParseMCU(struct Line **prev,struct Line **top)
{ 
#if ACCUSOFT_CODE
  UBYTE i;
  
  
  for(i = 0;i < m_ucCount;i++) {
    class HuffmanDecoder *dc = m_pDCDecoder[i];
    struct Line *line = top[i];
    struct Line *pline= prev[i];
    UBYTE ym = m_ucMCUHeight[i];
    class PredictorBase *mcupred = m_pPredict[i];
    LONG *lp = line->m_pData + m_ulX[i];
    LONG *pp = (pline)?(pline->m_pData + m_ulX[i]):(NULL);
    
    
    do {
      class PredictorBase *pred = mcupred;
      UBYTE xm = m_ucMCUWidth[i];
      do {
        LONG v;
        UBYTE symbol = dc->Get(&m_Stream);
        
        if (symbol == 0) {
          v = 0;
        } else if (symbol == 16) {
          v = -32768;
        } else {
          LONG thre = 1L << (symbol - 1);
          LONG diff = m_Stream.Get(symbol); 
          if (diff < thre) {
            diff += (-1L << symbol) + 1;
          }
          v = diff;
        }
        
        
        lp[0] = pred->DecodeSample(v,lp,pp);
        
        
        
      } while(--xm && (lp++,pp++,pred = pred->MoveRight(),true));
      
      
    } while(--ym && (pp = line->m_pData + m_ulX[i],line = (line->m_pNext)?(line->m_pNext):(line),
                     lp = line->m_pData + m_ulX[i],mcupred = mcupred->MoveDown(),true));
  }
#else
  NOREF(prev);
  NOREF(top);
#endif
}