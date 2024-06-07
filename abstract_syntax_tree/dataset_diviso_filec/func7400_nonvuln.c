void SampleInterleavedLSScan::FindComponentDimensions(void)
{ 
#if ACCUSOFT_CODE
  UBYTE cx;
  
  JPEGLSScan::FindComponentDimensions();

  
  
  for(cx = 0;cx < m_ucCount;cx++) {
    class Component *comp = ComponentOf(cx);
    if (comp->MCUHeightOf() != 1 || comp->MCUWidthOf() != 1)
      JPG_THROW(INVALID_PARAMETER,"STR",
                "STR");
  }
#endif
}