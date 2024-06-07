static inline void ModulateHSV(const double percent_hue,
  const double percent_saturation,const double percent_value,double *red,
  double *green,double *blue)
{
  double
    hue,
    saturation,
    value;

  
  ConvertRGBToHSV(*red,*green,*blue,&hue,&saturation,&value);
  hue+=0.5*(0.01*percent_hue-1.0);
  while (hue < 0.0)
    hue+=1.0;
  while (hue >= 1.0)
    hue-=1.0;
  saturation*=0.01*percent_saturation;
  value*=0.01*percent_value;
  ConvertHSVToRGB(hue,saturation,value,red,green,blue);
}