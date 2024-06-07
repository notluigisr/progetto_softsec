ModuleExport size_t RegisterSFWImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadSFWImage;
  entry->magick=(IsImageFormatHandler *) IsSFW;
  entry->flags^=CoderAdjoinFlag;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}