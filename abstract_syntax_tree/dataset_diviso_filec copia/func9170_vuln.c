static inline unsigned int ScaleQuantumToMap(const Quantum quantum)
{
  if (quantum >= (Quantum) MaxMap)
    return((unsigned int) MaxMap);
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned int) quantum);
#else
  if (quantum < 0.0)
    return(0UL);
  return((unsigned int) (quantum+0.5));
#endif
}