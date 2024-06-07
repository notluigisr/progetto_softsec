ModuleExport size_t RegisterCALSImage(void)
{



  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR",CALSDescription);
  entry->decoder=(DecodeImageHandler *) ReadCALSImage;
#if defined(MAGICKCORE_TIFF_DELEGATE)
  entry->encoder=(EncodeImageHandler *) WriteCALSImage;
#endif
  entry->flags^=CoderAdjoinFlag;
  entry->magick=(IsImageFormatHandler *) IsCALS;
  entry->note=ConstantString(CALSNote);
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",CALSDescription);
  entry->decoder=(DecodeImageHandler *) ReadCALSImage;
#if defined(MAGICKCORE_TIFF_DELEGATE)
  entry->encoder=(EncodeImageHandler *) WriteCALSImage;
#endif
  entry->flags^=CoderAdjoinFlag;
  entry->magick=(IsImageFormatHandler *) IsCALS;
  entry->note=ConstantString(CALSNote);
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}