static MagickBooleanType WriteINLINEImage(const ImageInfo *image_info,
  Image *image,ExceptionInfo *exception)
{
  char
    *base64,
    message[MagickPathExtent];

  const MagickInfo
    *magick_info;

  Image
    *write_image;

  ImageInfo
    *write_info;

  MagickBooleanType
    status;

  size_t
    blob_length,
    encode_length;

  unsigned char
    *blob;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",image->filename);
  write_info=CloneImageInfo(image_info);
  (void) SetImageInfo(write_info,1,exception);
  if (LocaleCompare(write_info->magick,"STR") == 0)
    (void) CopyMagickString(write_info->magick,image->magick,MagickPathExtent);
  magick_info=GetMagickInfo(write_info->magick,exception);
  if ((magick_info == (const MagickInfo *) NULL) ||
      (GetMagickMimeType(magick_info) == (const char *) NULL))
    ThrowWriterException(CorruptImageError,"STR");
  (void) CopyMagickString(image->filename,write_info->filename,
    MagickPathExtent);
  blob_length=2048;
  write_image=CloneImage(image,0,0,MagickTrue,exception);
  if (write_image == (Image *) NULL)
    {
      write_info=DestroyImageInfo(write_info);
      return(MagickTrue);
    }
  blob=(unsigned char *) ImageToBlob(write_info,write_image,&blob_length,
    exception);
  write_image=DestroyImage(write_image);
  write_info=DestroyImageInfo(write_info);
  if (blob == (unsigned char *) NULL)
    return(MagickFalse);
  encode_length=0;
  base64=Base64Encode(blob,blob_length,&encode_length);
  blob=(unsigned char *) RelinquishMagickMemory(blob);
  if (base64 == (char *) NULL)
    ThrowWriterException(ResourceLimitError,"STR");
  
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,exception);
  if (status == MagickFalse)
    {
      base64=DestroyString(base64);
      return(status);
    }
  (void) FormatLocaleString(message,MagickPathExtent,"STR",
    GetMagickMimeType(magick_info));
  (void) WriteBlobString(image,message);
  (void) WriteBlobString(image,base64);
  base64=DestroyString(base64);
  return(MagickTrue);
}