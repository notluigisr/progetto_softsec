static double Hann(const double x,
  const ResizeFilter *magick_unused(resize_filter))
{
  
  const double cosine=cos((double) (MagickPI*x));
  magick_unreferenced(resize_filter);
  return(0.5+0.5*cosine);
}