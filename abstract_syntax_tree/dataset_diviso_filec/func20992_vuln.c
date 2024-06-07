static inline MagickSizeType ScaleQuantumToLongLong(const Quantum quantum)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((MagickSizeType) (MagickULLConstant(281479271743489)*quantum));
#else
  if (quantum <= 0.0)
    return(0UL);
  if ((281479271743489.0*quantum) >= 18446744073709551615.0)
    return(MagickULLConstant(18446744073709551615));
  return((MagickSizeType) (281479271743489.0*quantum+0.5));
#endif
}