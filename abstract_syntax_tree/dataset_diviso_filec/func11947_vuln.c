static MagickBooleanType Huffman2DEncodeImage(const ImageInfo *image_info,
  Image *image,Image *inject_image,ExceptionInfo *exception)
{
  Image
    *group4_image;

  ImageInfo
    *write_info;

  MagickBooleanType
    status;

  size_t
    length;

  unsigned char
    *group4;

  status=MagickTrue;
  write_info=CloneImageInfo(image_info);
  (void) CopyMagickString(write_info->filename,"STR",MagickPathExtent);
  (void) CopyMagickString(write_info->magick,"STR",MagickPathExtent);
  group4_image=CloneImage(inject_image,0,0,MagickTrue,exception);
  if (group4_image == (Image *) NULL)
    return(MagickFalse);
  group4=(unsigned char *) ImageToBlob(write_info,group4_image,&length,
    exception);
  group4_image=DestroyImage(group4_image);
  if (group4 == (unsigned char *) NULL)
    return(MagickFalse);
  write_info=DestroyImageInfo(write_info);
  if (WriteBlob(image,length,group4) != (ssize_t) length)
    status=MagickFalse;
  group4=(unsigned char *) RelinquishMagickMemory(group4);
  return(status);
}