static inline void ModulateHWB(const double percent_hue,
  const double percent_whiteness,const double percent_blackness,double *red,
  double *green,double *blue)
{
  double
    blackness,
    hue,
    whiteness;

  
  ConvertRGBToHWB(*red,*green,*blue,&hue,&whiteness,&blackness);
  hue+=0.5*(0.01*percent_hue-1.0);
  while (hue < 0.0)
    hue+=1.0;
  while (hue >= 1.0)
    hue-=1.0;
  blackness*=0.01*percent_blackness;
  whiteness*=0.01*percent_whiteness;
  ConvertHWBToRGB(hue,whiteness,blackness,red,green,blue);
}