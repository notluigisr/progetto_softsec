static inline QuantumAny ScaleQuantumToAny(const Quantum quantum,
  const QuantumAny range)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
  return((QuantumAny) ((double) range*quantum/QuantumRange));
#else
  if (quantum <= 0.0)
    return((QuantumAny) 0UL);
  if (((double) range*quantum/QuantumRange) >= 18446744073709551615.0)
    return((QuantumAny) MagickULLConstant(18446744073709551615));
  return((QuantumAny) ((double) range*quantum/QuantumRange+0.5));
#endif
}