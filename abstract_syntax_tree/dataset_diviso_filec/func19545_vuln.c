ModuleExport size_t RegisterXWDImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("STR");
#if defined(MAGICKCORE_X11_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadXWDImage;
  entry->encoder=(EncodeImageHandler *) WriteXWDImage;
#endif
  entry->magick=(IsImageFormatHandler *) IsXWD;
  entry->adjoin=MagickFalse;
  entry->description=ConstantString("STR");
  entry->module=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}