static inline void ModulateHSB(const double percent_hue,
  const double percent_saturation,const double percent_brightness,double *red,
  double *green,double *blue)
{
  double
    brightness,
    hue,
    saturation;

  
  ConvertRGBToHSB(*red,*green,*blue,&hue,&saturation,&brightness);
  hue+=0.5*(0.01*percent_hue-1.0);
  while (hue < 0.0)
    hue+=1.0;
  while (hue > 1.0)
    hue-=1.0;
  saturation*=0.01*percent_saturation;
  brightness*=0.01*percent_brightness;
  ConvertHSBToRGB(hue,saturation,brightness,red,green,blue);
}