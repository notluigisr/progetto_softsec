static inline unsigned char ScaleQuantumToChar(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned char) ((quantum+MagickULLConstant(8421504))/
    MagickULLConstant(16843009)));
#else
  if (quantum <= 0.0)
    return(0);
  if ((quantum/16843009.0) >= 255.0)
    return(255);
  return((unsigned char) (quantum/16843009.0+0.5));
#endif
}