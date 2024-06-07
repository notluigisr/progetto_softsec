static inline unsigned short ScaleQuantumToShort(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned short) quantum);
#else
  if (quantum <= 0.0)
    return(0);
  if (quantum >= 65535.0)
    return(65535);
  return((unsigned short) (quantum+0.5));
#endif
}