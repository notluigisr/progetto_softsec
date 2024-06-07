ModuleExport size_t RegisterPCXImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPCXImage;
  entry->encoder=(EncodeImageHandler *) WritePCXImage;
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags|=CoderEncoderSeekableStreamFlag;
  entry->magick=(IsImageFormatHandler *) IsDCX;
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPCXImage;
  entry->encoder=(EncodeImageHandler *) WritePCXImage;
  entry->magick=(IsImageFormatHandler *) IsPCX;
  entry->flags^=CoderAdjoinFlag;
  entry->flags|=CoderDecoderSeekableStreamFlag;
  entry->flags|=CoderEncoderSeekableStreamFlag;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}