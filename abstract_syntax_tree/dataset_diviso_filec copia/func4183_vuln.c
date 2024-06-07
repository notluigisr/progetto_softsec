static inline unsigned short ScaleQuantumToShort(const Quantum quantum)
{
  if (quantum <= 0.0)
    return(0);
  if ((quantum/281479271743489.0) >= 65535.0)
    return(65535);
  return((unsigned short) (quantum/281479271743489.0+0.5));
}