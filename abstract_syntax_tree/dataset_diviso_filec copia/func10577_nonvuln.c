static inline void AffineArgsToCoefficients(double *affine)
{
  
  double tmp[4];  
  tmp[0]=affine[1]; tmp[1]=affine[2]; tmp[2]=affine[3]; tmp[3]=affine[4];
  affine[3]=tmp[0]; affine[1]=tmp[1]; affine[4]=tmp[2]; affine[2]=tmp[3];
}