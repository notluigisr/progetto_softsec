static inline MagickSizeType ScaleQuantumToLongLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((MagickSizeType) (MagickULLConstant(4294967297)*quantum));
#else
  if (quantum <= 0.0)
    return(0UL);
  if ((4294967297.0*quantum) >= 18446744073709551615.0)
    return(MagickULLConstant(18446744073709551615));
  return((MagickSizeType) (4294967297.0*quantum+0.5));
#endif
}