ModuleExport size_t RegisterDCMImage(void)
{
  MagickInfo
    *entry;

  static const char
    *DCMNote=
    {
      "STR"
      "STR"
      "STR"
      "STR"
      "STR"
    };

  entry=AcquireMagickInfo("STR",
    "STR");
  entry->decoder=(DecodeImageHandler *) ReadDCMImage;
  entry->magick=(IsImageFormatHandler *) IsDCM;
  entry->flags^=CoderAdjoinFlag;
  entry->flags|=CoderSeekableStreamFlag;
  entry->note=ConstantString(DCMNote);
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}