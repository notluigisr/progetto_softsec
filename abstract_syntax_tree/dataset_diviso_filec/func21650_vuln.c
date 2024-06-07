static inline unsigned int ScaleQuantumToMap(const Quantum quantum)
{
  if (quantum <= 0.0)
    return(0UL);
  if ((quantum/281479271743489.0) >= MaxMap)
    return((unsigned int) MaxMap);
  return((unsigned int) (quantum/281479271743489.0+0.5));
}