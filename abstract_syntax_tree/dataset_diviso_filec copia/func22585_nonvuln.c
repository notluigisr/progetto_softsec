CopyRgbToGopPixel (
  OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *BitMapOut,
  IN  EFI_HII_RGB_PIXEL              *BitMapIn,
  IN  UINTN                          PixelNum
  )
{
  UINTN Index;

  ASSERT (BitMapOut != NULL && BitMapIn != NULL);

  for (Index = 0; Index < PixelNum; Index++) {
    CopyMem (BitMapOut + Index, BitMapIn + Index, sizeof (EFI_HII_RGB_PIXEL));
  }
}