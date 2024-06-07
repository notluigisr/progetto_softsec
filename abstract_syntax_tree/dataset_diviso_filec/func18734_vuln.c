static inline unsigned int ScaleQuantumToMap(const Quantum quantum)
{
  if (quantum < 0.0)
    return(0UL);
  if ((quantum/65537) >= (Quantum) MaxMap)
    return((unsigned int) MaxMap);
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((unsigned int) ((quantum+MagickULLConstant(32768))/
    MagickULLConstant(65537)));
#else
  return((unsigned int) (quantum/65537.0+0.5));
#endif
}