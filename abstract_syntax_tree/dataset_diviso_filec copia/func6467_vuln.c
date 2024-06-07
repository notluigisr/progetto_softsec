static MagickBooleanType WriteTHUMBNAILImage(const ImageInfo *image_info,
  Image *image,ExceptionInfo *exception)
{
  const char
    *property;

  const StringInfo
    *profile;

  Image
    *thumbnail_image;

  ImageInfo
    *write_info;

  MagickBooleanType
    status;

  ssize_t
    i;

  size_t
    length;

  ssize_t
    offset;

  unsigned char
    *q;

  profile=GetImageProfile(image,"STR");
  if (profile == (const StringInfo *) NULL)
    ThrowWriterException(CoderError,"STR");
  property=GetImageProperty(image,"STR",exception);
  if (property == (const char *) NULL)
    ThrowWriterException(CoderError,"STR");
  offset=(ssize_t) StringToLong(property);
  if (offset < 0)
    ThrowWriterException(CoderError,"STR");
  property=GetImageProperty(image,"STR",exception);
  if (property == (const char *) NULL)
    ThrowWriterException(CoderError,"STR");
  length=(size_t) StringToLong(property);
  q=GetStringInfoDatum(profile)+offset;
  for (i=offset; i < (ssize_t) GetStringInfoLength(profile) - 3; i++)
  {
    if (memcmp(q,"STR",3) == 0)
      break;
    q++;
  }
  if ((q+length) > (GetStringInfoDatum(profile)+GetStringInfoLength(profile)))
    ThrowWriterException(CoderError,"STR");
  thumbnail_image=BlobToImage(image_info,q,length,exception);
  if (thumbnail_image == (Image *) NULL)
    return(MagickFalse);
  (void) SetImageType(thumbnail_image,thumbnail_image->alpha_trait ==
    UndefinedPixelTrait ? TrueColorType : TrueColorAlphaType,exception);
  (void) CopyMagickString(thumbnail_image->filename,image->filename,
    MagickPathExtent);
  write_info=CloneImageInfo(image_info);
  *write_info->magick='\0';
  (void) SetImageInfo(write_info,1,exception);
  if ((*write_info->magick == '\0') ||
      (LocaleCompare(write_info->magick,"STR") == 0))
    (void) FormatLocaleString(thumbnail_image->filename,MagickPathExtent,
      "STR",write_info->filename);
  status=WriteImage(write_info,thumbnail_image,exception);
  thumbnail_image=DestroyImage(thumbnail_image);
  write_info=DestroyImageInfo(write_info);
  return(status);
}