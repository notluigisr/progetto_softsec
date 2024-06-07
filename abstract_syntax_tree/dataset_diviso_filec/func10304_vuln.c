static inline Quantum ClampToQuantum(const MagickRealType value)
{
#if defined(MAGICKCORE_HDRI_SUPPORT)
  return((Quantum) value);
#else
  if (value <= 0.0f)
    return((Quantum) 0);
  if (value >= (MagickRealType) QuantumRange)
    return(QuantumRange);
  return((Quantum) (value+0.5f));
#endif
}