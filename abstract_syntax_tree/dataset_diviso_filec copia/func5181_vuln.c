DLLEXPORT unsigned long tjBufSize(int width, int height, int jpegSubsamp)
{
  unsigned long retval = 0;
  int mcuw, mcuh, chromasf;

  if (width < 1 || height < 1 || jpegSubsamp < 0 || jpegSubsamp >= NUMSUBOPT)
    THROWG("STR");

  
  mcuw = tjMCUWidth[jpegSubsamp];
  mcuh = tjMCUHeight[jpegSubsamp];
  chromasf = jpegSubsamp == TJSAMP_GRAY ? 0 : 4 * 64 / (mcuw * mcuh);
  retval = PAD(width, mcuw) * PAD(height, mcuh) * (2 + chromasf) + 2048;

bailout:
  return retval;
}