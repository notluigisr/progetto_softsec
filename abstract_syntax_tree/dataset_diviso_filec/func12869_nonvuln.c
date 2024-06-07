static Image *ReadPNGImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  Image
    *image;

  MagickBooleanType
    logging,
    status;

  MngInfo
    *mng_info;

  char
    magic_number[MaxTextExtent];

  ssize_t
    count;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);

  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",
      image_info->filename);

  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  logging=LogMagickEvent(CoderEvent,GetMagickModule(),"STR");
  image=AcquireImage(image_info);
  mng_info=(MngInfo *) NULL;
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);

  if (status == MagickFalse)
    return(DestroyImageList(image));

  
  count=ReadBlob(image,8,(unsigned char *) magic_number);

  if ((count < 8) || (memcmp(magic_number,"STR",8) != 0))
    ThrowReaderException(CorruptImageError,"STR");

  
  if (GetBlobSize(image) < 61)
    ThrowReaderException(CorruptImageError,"STR");

  
  mng_info=(MngInfo *) AcquireMagickMemory(sizeof(MngInfo));

  if (mng_info == (MngInfo *) NULL)
    ThrowReaderException(ResourceLimitError,"STR");

  
  (void) memset(mng_info,0,sizeof(MngInfo));
  mng_info->image=image;

  image=ReadOnePNGImage(mng_info,image_info,exception);
  mng_info=MngInfoFreeStruct(mng_info);

  if (image == (Image *) NULL)
    {
      if (logging != MagickFalse)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
          "STR");

      return((Image *) NULL);
    }

  (void) CloseBlob(image);

  if ((image->columns == 0) || (image->rows == 0))
    {
      if (logging != MagickFalse)
        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
          "STR");

      ThrowReaderException(CorruptImageError,"STR");
    }

  if ((IssRGBColorspace(image->colorspace) != MagickFalse) &&
      ((image->gamma < .45) || (image->gamma > .46)) &&
           !(image->chromaticity.red_primary.x>0.6399f &&
           image->chromaticity.red_primary.x<0.6401f &&
           image->chromaticity.red_primary.y>0.3299f &&
           image->chromaticity.red_primary.y<0.3301f &&
           image->chromaticity.green_primary.x>0.2999f &&
           image->chromaticity.green_primary.x<0.3001f &&
           image->chromaticity.green_primary.y>0.5999f &&
           image->chromaticity.green_primary.y<0.6001f &&
           image->chromaticity.blue_primary.x>0.1499f &&
           image->chromaticity.blue_primary.x<0.1501f &&
           image->chromaticity.blue_primary.y>0.0599f &&
           image->chromaticity.blue_primary.y<0.0601f &&
           image->chromaticity.white_point.x>0.3126f &&
           image->chromaticity.white_point.x<0.3128f &&
           image->chromaticity.white_point.y>0.3289f &&
           image->chromaticity.white_point.y<0.3291f))
    {
       (void) LogMagickEvent(CoderEvent,GetMagickModule(),
          "STR");
       SetImageColorspace(image,RGBColorspace);
    }

  if (logging != MagickFalse)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "STR",
            (double) image->page.width,(double) image->page.height,
            (double) image->page.x,(double) image->page.y);

  if (logging != MagickFalse)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),"STR");

  return(image);
}