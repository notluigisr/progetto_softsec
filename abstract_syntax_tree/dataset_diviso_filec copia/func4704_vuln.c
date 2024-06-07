static inline QuantumAny ScaleQuantumToAny(const Quantum quantum,
  const QuantumAny range)
{
  if (quantum < 0)
    return((QuantumAny) 0);
  return((QuantumAny) (((double) range*quantum)/QuantumRange+0.5));
}