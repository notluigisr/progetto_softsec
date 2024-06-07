ModuleExport size_t RegisterPNMImage(void)
{
  MagickInfo
    *entry;

  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->description=ConstantString("STR");
  entry->mime_type=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->description=ConstantString("STR");
  entry->mime_type=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->endian_support=MagickTrue;
  entry->description=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->description=ConstantString("STR");
  entry->mime_type=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->magick=(IsImageFormatHandler *) IsPNM;
  entry->description=ConstantString("STR");
  entry->mime_type=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  entry=SetMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPNMImage;
  entry->encoder=(EncodeImageHandler *) WritePNMImage;
  entry->description=ConstantString("STR");
  entry->mime_type=ConstantString("STR");
  entry->module=ConstantString("STR");
  entry->seekable_stream=MagickTrue;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}