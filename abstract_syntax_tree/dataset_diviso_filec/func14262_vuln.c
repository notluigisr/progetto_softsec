ModuleExport size_t RegisterPSImage(void)
{
  MagickInfo
    *entry;

  entry=AcquireMagickInfo("STR",
    "STR");
  entry->decoder=(DecodeImageHandler *) ReadPSImage;
  entry->encoder=(EncodeImageHandler *) WritePSImage;
  entry->magick=(IsImageFormatHandler *) IsPS;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderBlobSupportFlag;
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPSImage;
  entry->encoder=(EncodeImageHandler *) WritePSImage;
  entry->magick=(IsImageFormatHandler *) IsPS;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderBlobSupportFlag;
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPSImage;
  entry->encoder=(EncodeImageHandler *) WritePSImage;
  entry->magick=(IsImageFormatHandler *) IsPS;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderBlobSupportFlag;
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",
    "STR");
  entry->decoder=(DecodeImageHandler *) ReadPSImage;
  entry->encoder=(EncodeImageHandler *) WritePSImage;
  entry->magick=(IsImageFormatHandler *) IsPS;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderBlobSupportFlag;
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR");
  entry->decoder=(DecodeImageHandler *) ReadPSImage;
  entry->encoder=(EncodeImageHandler *) WritePSImage;
  entry->magick=(IsImageFormatHandler *) IsPS;
  entry->mime_type=ConstantString("STR");
  entry->flags^=CoderBlobSupportFlag;
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}