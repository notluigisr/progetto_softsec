ModuleExport size_t RegisterRLEImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadRLEImage;
  entry->magick=(IsImageFormatHandler *) IsRLE;
  entry->flags^=CoderAdjoinFlag;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}