static MagickBooleanType TIFFWritePhotoshopLayers(Image* image,
  const ImageInfo *image_info,ExceptionInfo *exception)
{
  BlobInfo
    *blob;

  CustomStreamInfo
    *custom_stream;

  Image
    *next;

  ImageInfo
    *clone_info;

  MagickBooleanType
    status;

  PhotoshopProfile
    profile;

  PSDInfo
    info;

  size_t
    length;

  StringInfo
    *layers;

  next=image->next;
  if (next == (Image *) NULL)
    return(MagickTrue);
  clone_info=CloneImageInfo(image_info);
  if (clone_info == (ImageInfo *) NULL)
      ThrowBinaryException(ResourceLimitError,"STR",
        image->filename);
  profile.offset=0;
  profile.quantum=MagickMinBlobExtent;
  layers=AcquireStringInfo(profile.quantum);
  if (layers == (StringInfo *) NULL)
    {
      clone_info=DestroyImageInfo(clone_info);
      ThrowBinaryException(ResourceLimitError,"STR",
        image->filename);
    }
  profile.data=layers;
  profile.extent=layers->length;
  custom_stream=TIFFAcquireCustomStreamForWriting(&profile,exception);
  if (custom_stream == (CustomStreamInfo *) NULL)
    {
      clone_info=DestroyImageInfo(clone_info);
      layers=DestroyStringInfo(layers);
      ThrowBinaryException(ResourceLimitError,"STR",
        image->filename);
    }
  blob=CloneBlobInfo((BlobInfo *) NULL);
  if (blob == (BlobInfo *) NULL)
    {
      clone_info=DestroyImageInfo(clone_info);
      layers=DestroyStringInfo(layers);
      custom_stream=DestroyCustomStreamInfo(custom_stream);
      ThrowBinaryException(ResourceLimitError,"STR",
        image->filename);
    }
  DestroyBlob(next);
  next->blob=blob;
  while (next != (Image *) NULL)
    next=SyncNextImageInList(next);
  next=image->next;
  AttachCustomStream(next->blob,custom_stream);
  InitPSDInfo(image,&info);
  if (next->endian == UndefinedEndian)
    next->endian=(HOST_FILLORDER == FILLORDER_LSB2MSB) ? LSBEndian : MSBEndian;
  WriteBlobString(next,"STR");
  WriteBlobByte(next,0);
  WriteBlobString(next,next->endian == LSBEndian ? "STR");
  status=WritePSDLayers(next,clone_info,&info,exception);
  if (status != MagickFalse)
    {
      SetStringInfoLength(layers,(size_t) profile.offset);
      status=SetImageProfile(image,"STR",layers,exception);
    }
  while (next != (Image *) NULL)
  {
    CloseBlob(next);
    next=next->next;
  }
  layers=DestroyStringInfo(layers);
  clone_info=DestroyImageInfo(clone_info);
  custom_stream=DestroyCustomStreamInfo(custom_stream);
  return(status);
}