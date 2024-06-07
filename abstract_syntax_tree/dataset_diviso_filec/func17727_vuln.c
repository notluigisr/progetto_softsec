static MagickBooleanType WriteCIPImage(const ImageInfo *image_info,Image *image,
  ExceptionInfo *exception)
{
  char
    buffer[MagickPathExtent];

  const char
    *value;

  MagickBooleanType
    status;

  register const Quantum
    *p;

  register ssize_t
    i,
    x;

  ssize_t
    y;

  unsigned char
    byte;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,exception);
  if (status == MagickFalse)
    return(status);
  (void) WriteBlobString(image,"STR");
  value=GetImageProperty(image,"STR",exception);
  if (value != (const char *) NULL)
    (void) FormatLocaleString(buffer,MagickPathExtent,"STR",value);
  else
    {
      char
        basename[MagickPathExtent];

      GetPathComponent(image->filename,BasePath,basename);
      (void) FormatLocaleString(buffer,MagickPathExtent,"STR",
        basename);
    }
  (void) WriteBlobString(image,buffer);
  (void) FormatLocaleString(buffer,MagickPathExtent,
    "STR",(double) image->page.x);
  (void) WriteBlobString(image,buffer);
  (void) FormatLocaleString(buffer,MagickPathExtent,
    "STR",(double) image->page.y);
  (void) WriteBlobString(image,buffer);
  (void) FormatLocaleString(buffer,MagickPathExtent,"STR",
    (double) (image->columns+(image->columns % 2)));
  (void) WriteBlobString(image,buffer);
  (void) FormatLocaleString(buffer,MagickPathExtent,"STR",
    (double) image->rows);
  (void) WriteBlobString(image,buffer);
  (void) FormatLocaleString(buffer,MagickPathExtent,"STR");
  (void) WriteBlobString(image,buffer);
  (void) WriteBlobString(image,"STR");
  (void) TransformImageColorspace(image,sRGBColorspace,exception);
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    p=GetVirtualPixels(image,0,y,image->columns,1,exception);
    if (p == (const Quantum *) NULL)
      break;
    for (x=0; x < ((ssize_t) image->columns-3); x+=4)
    {
      byte=(unsigned char)
        ((((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+3))/QuantumRange) & 0x03) << 6) |
         (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+2))/QuantumRange) & 0x03) << 4) |
         (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+1))/QuantumRange) & 0x03) << 2) |
         (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+0))/QuantumRange) & 0x03) << 0));
      (void) FormatLocaleString(buffer,MagickPathExtent,"STR",byte);
      (void) WriteBlobString(image,buffer);
      p+=4;
    }
    if ((image->columns % 4) != 0)
      {
        i=(ssize_t) image->columns % 4;
        byte=(unsigned char)
          ((((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+MagickMin(i,3)))/QuantumRange) & 0x03) << 6) |
           (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+MagickMin(i,2)))/QuantumRange) & 0x03) << 4) |
           (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+MagickMin(i,1)))/QuantumRange) & 0x03) << 2) |
           (((size_t) (3*ClampToQuantum(GetPixelLuma(image,p+MagickMin(i,0)))/QuantumRange) & 0x03) << 0));
        (void) FormatLocaleString(buffer,MagickPathExtent,"STR",~byte);
        (void) WriteBlobString(image,buffer);
      }
    status=SetImageProgress(image,SaveImageTag,(MagickOffsetType) y,
      image->rows);
    if (status == MagickFalse)
      break;
  }
  (void) WriteBlobString(image,"STR");
  (void) WriteBlobString(image,"STR");
  (void) CloseBlob(image);
  return(MagickTrue);
}