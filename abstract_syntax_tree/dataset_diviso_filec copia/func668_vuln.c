static inline MagickSizeType ScaleQuantumToLongLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((MagickSizeType) (MagickULLConstant(72340172838076673)*quantum));
#else
  if (quantum <= 0.0)
    return(0UL);
  if ((72340172838076673.0*quantum) >= 18446744073709551615.0)
    return(MagickULLConstant(18446744073709551615));
  return((MagickSizeType) (72340172838076673*quantum+0.5));
#endif
}