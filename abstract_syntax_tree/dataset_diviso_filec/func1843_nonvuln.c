void LosslessScan::MeasureMCU(struct Line **prev,struct Line **top)
{
#if ACCUSOFT_CODE
  UBYTE i;
  
  
  for(i = 0;i < m_ucCount;i++) {
    class HuffmanStatistics *dcstat = m_pDCStatistics[i];
    struct Line *line = top[i];
    struct Line *pline= prev[i];
    class PredictorBase *mcupred = m_pPredict[i];
    UBYTE ym = m_ucMCUHeight[i];
    LONG *lp = line->m_pData + m_ulX[i];
    LONG *pp = (pline)?(pline->m_pData + m_ulX[i]):(NULL);
    
    
    
    do {
      class PredictorBase *pred = mcupred;
      UBYTE xm = m_ucMCUWidth[i];
      do {
        
        
        LONG v = pred->EncodeSample(lp,pp);
        
        if (v == 0) {
          dcstat->Put(0);
        } else if (v == -32768) {
          dcstat->Put(16); 
        } else {
          UBYTE symbol = 0;
          do {
            symbol++;
            if (v > -(1 << symbol) && v < (1 << symbol)) {
              dcstat->Put(symbol);
              break;
            }
          } while(true);
        }
        
        
        
      } while(--xm && (lp++,pp++,pred = pred->MoveRight(),true));
      
      
    } while(--ym && (pp = line->m_pData + m_ulX[i],line = (line->m_pNext)?(line->m_pNext):(line),
                     lp = line->m_pData + m_ulX[i],mcupred = mcupred->MoveDown(),true));
  }
#else
  NOREF(prev);
  NOREF(top);
#endif
}