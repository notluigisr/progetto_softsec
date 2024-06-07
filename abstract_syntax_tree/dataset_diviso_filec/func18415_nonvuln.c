void HierarchicalBitmapRequester::Allocate8Lines(UBYTE c)
{
  int cnt;
  ULONG y = m_pulY[c];
  
  
  for(cnt = 0;cnt < 8 && y < m_pulHeight[c];cnt++) {
    assert(m_ppEncodingMCU[cnt | (c << 3)] == NULL);
    m_ppEncodingMCU[cnt | (c << 3)] = m_pLargestScale->AllocateLine(c);
    y++;
  }
}