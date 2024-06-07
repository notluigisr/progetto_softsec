static inline unsigned int ScaleQuantumToLong(const Quantum quantum)
{
  return((unsigned int) (quantum/4294967297.0+0.5));
}