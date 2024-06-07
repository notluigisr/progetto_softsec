ModuleExport size_t RegisterHDRImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadHDRImage;
  entry->encoder=(EncodeImageHandler *) WriteHDRImage;
  entry->magick=(IsImageFormatHandler *) IsHDR;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}