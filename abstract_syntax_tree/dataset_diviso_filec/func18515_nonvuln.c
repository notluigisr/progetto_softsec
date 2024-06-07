ModuleExport size_t RegisterJPEGImage(void)
{


  char
    version[MagickPathExtent];

  MagickInfo
    *entry;

  *version='\0';
#if defined(JPEG_LIB_VERSION)
  (void) FormatLocaleString(version,MagickPathExtent,"STR",JPEG_LIB_VERSION);
#endif
  entry=AcquireMagickInfo("STR",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->magick=(IsImageFormatHandler *) IsJPEG;
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->magick=(IsImageFormatHandler *) IsJPEG;
  entry->flags^=CoderAdjoinFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  entry=AcquireMagickInfo("STR",JPEGDescription);
#if (JPEG_LIB_VERSION < 80) && !defined(LIBJPEG_TURBO_VERSION)
  entry->flags^=CoderDecoderThreadSupportFlag;
#endif
#if defined(MAGICKCORE_JPEG_DELEGATE)
  entry->decoder=(DecodeImageHandler *) ReadJPEGImage;
  entry->encoder=(EncodeImageHandler *) WriteJPEGImage;
#endif
  entry->flags^=CoderAdjoinFlag;
  entry->flags^=CoderUseExtensionFlag;
  if (*version != '\0')
    entry->version=ConstantString(version);
  entry->mime_type=ConstantString("STR");
  (void) RegisterMagickInfo(entry);
  return(MagickImageCoderSignature);
}