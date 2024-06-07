ModuleExport size_t RegisterPCXImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPCXImage;
  entry->encoder=(EncodeImageHandler *) WritePCXImage;
  entry->seekable_stream=MagickTrue;
  entry->magick=(IsImageFormatHandler *) IsDCX;
  entry->description=ConstantString("STR");
  entry->module=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPCXImage;
  entry->encoder=(EncodeImageHandler *) WritePCXImage;
  entry->magick=(IsImageFormatHandler *) IsPCX;
  entry->adjoin=MagickFalse;
  entry->seekable_stream=MagickTrue;
  entry->description=ConstantString("STR");
  entry->module=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}