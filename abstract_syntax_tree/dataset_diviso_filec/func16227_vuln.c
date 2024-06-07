ModuleExport size_t RegisterWEBPImage(void)
{
  char
    version[MagickPathExtent];

  MagickInfo
    *entry;

  *version='\0';
  entry=AcquireMagickInfo("STR");
#if defined(MAGICKCORE_WEBP_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadWEBPImage;
  entry->encoder=(EncodeImageHandler *) WriteWEBPImage;
  (void) FormatLocaleString(version,MagickPathExtent,"STR",
    (WebPGetDecoderVersion() >> 16) & 0xff,
    (WebPGetDecoderVersion() >> 8) & 0xff,
    (WebPGetDecoderVersion() >> 0) & 0xff,WEBP_DECODER_ABI_VERSION);
#endif
  entry->mime_type=ConstantString("STR");
  entry->flags^=CoderAdjoinFlag;
  entry->magick=(IsImageFormatHandler *) IsWEBP;
  if (*version != '\0')
    entry->version=ConstantString(version);
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}