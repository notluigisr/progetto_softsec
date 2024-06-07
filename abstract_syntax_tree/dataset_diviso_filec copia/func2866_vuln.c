static inline unsigned int ScaleQuantumToLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned int) quantum);
#else
  if (quantum <= 0.0)
    return(0);
  if ((quantum) >= 4294967295.0)
    return(4294967295);
  return((unsigned int) (quantum+0.5));
#endif
}