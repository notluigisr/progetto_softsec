Output8bitPixel (
  IN OUT EFI_IMAGE_INPUT             *Image,
  IN UINT8                           *Data,
  IN EFI_HII_IMAGE_PALETTE_INFO      *PaletteInfo
  )
{
  UINT16                             Xpos;
  UINT16                             Ypos;
  UINTN                              OffsetY;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL      *BitMapPtr;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL      PaletteValue[256];
  EFI_HII_IMAGE_PALETTE_INFO         *Palette;
  UINTN                              PaletteSize;
  UINT16                             PaletteNum;
  UINT8                              Byte;

  ASSERT (Image != NULL && Data != NULL && PaletteInfo != NULL);

  BitMapPtr = Image->Bitmap;

  
  
  
  PaletteSize = 0;
  CopyMem (&PaletteSize, PaletteInfo, sizeof (UINT16));
  PaletteSize += sizeof (UINT16);
  Palette = AllocateZeroPool (PaletteSize);
  ASSERT (Palette != NULL);
  if (Palette == NULL) {
    return;
  }
  CopyMem (Palette, PaletteInfo, PaletteSize);
  PaletteNum = (UINT16)(Palette->PaletteSize / sizeof (EFI_HII_RGB_PIXEL));
  ZeroMem (PaletteValue, sizeof (PaletteValue));
  CopyRgbToGopPixel (PaletteValue, Palette->PaletteValue, PaletteNum);
  FreePool (Palette);

  
  
  
  for (Ypos = 0; Ypos < Image->Height; Ypos++) {
    OffsetY = BITMAP_LEN_8_BIT ((UINT32) Image->Width, Ypos);
    
    
    
    for (Xpos = 0; Xpos < Image->Width; Xpos++) {
      Byte = *(Data + OffsetY + Xpos);
      BitMapPtr[OffsetY + Xpos] = PaletteValue[Byte];
    }
  }

}