static inline unsigned int ScaleQuantumToLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned int) (65537UL*quantum));
#else
  if (quantum <= 0.0)
    return(0UL);
  if ((65537.0*quantum) >= 4294967295.0)
    return(4294967295U);
  return((unsigned int) (65537.0*quantum+0.5));
#endif
}