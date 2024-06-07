MagickPrivate void ConvertRGBToLCHab(const double red,const double green,
  const double blue,double *luma,double *chroma,double *hue)
{
  double
    X,
    Y,
    Z;

  
  assert(luma != (double *) NULL);
  assert(chroma != (double *) NULL);
  assert(hue != (double *) NULL);
  ConvertRGBToXYZ(red,green,blue,&X,&Y,&Z);
  ConvertXYZToLCHab(X,Y,Z,luma,chroma,hue);
}