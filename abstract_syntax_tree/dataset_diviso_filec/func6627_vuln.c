EntropyParser::EntropyParser(class Frame *frame,class Scan *scan)
  : JKeeper(scan->EnvironOf()), m_pScan(scan), m_pFrame(frame)
{
  m_ucCount = scan->ComponentsInScan();

  
  
  for(volatile UBYTE i = 0;i < m_ucCount && i < 4;i++) {
    JPG_TRY {
      m_pComponent[i] = scan->ComponentOf(i);
    } JPG_CATCH {
      m_pComponent[i] = NULL;
    } JPG_ENDTRY;
  }

  m_ulRestartInterval   = m_pFrame->TablesOf()->RestartIntervalOf();
  m_usNextRestartMarker = 0xffd0;
  m_ulMCUsToGo          = m_ulRestartInterval;
  m_bSegmentIsValid     = true;
  m_bScanForDNL         = (m_pFrame->HeightOf() == 0)?true:false;
  m_bDNLFound           = false;
}