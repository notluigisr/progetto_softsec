static inline unsigned char ScaleQuantumToChar(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned char) quantum);
#else
  if (quantum <= 0.0)
    return(0);
  if (quantum >= 255.0)
    return(255);
  return((unsigned char) (quantum+0.5));
#endif
}