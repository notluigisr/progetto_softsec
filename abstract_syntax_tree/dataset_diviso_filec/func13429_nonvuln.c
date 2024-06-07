ModuleExport size_t RegisterCUTImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadCUTImage;
  entry->seekable_stream=MagickTrue;
  entry->description=ConstantString("STR");
  entry->module=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}