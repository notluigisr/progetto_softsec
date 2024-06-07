static inline MagickSizeType ScaleQuantumToLongLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((MagickSizeType) quantum);
#else
  if (quantum <= 0.0)
    return(0);
  if (quantum >= 18446744073709551615.0)
    return(MagickULLConstant(18446744073709551615));
  return((MagickSizeType) (quantum+0.5));
#endif
}