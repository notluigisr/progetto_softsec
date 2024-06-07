static inline Quantum ClampPixel(const MagickRealType value)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((Quantum) value);
#else
  if (value < 0.0f)
    return(0.0);
  if (value >= (MagickRealType) QuantumRange)
    return((Quantum) QuantumRange);
  return(value);
#endif
}