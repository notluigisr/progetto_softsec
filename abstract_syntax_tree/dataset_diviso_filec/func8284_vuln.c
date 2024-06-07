static Image *ReadGROUP4Image(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
  char
    filename[MagickPathExtent];

  FILE
    *file;

  Image
    *image;

  ImageInfo
    *read_info;

  int
    c,
    unique_file;

  MagickBooleanType
    status;

  size_t
    length;

  ssize_t
    offset,
    strip_offset;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",
      image_info->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  image=AcquireImage(image_info,exception);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFalse)
    {
      image=DestroyImageList(image);
      return((Image *) NULL);
    }
  
  file=(FILE *) NULL;
  unique_file=AcquireUniqueFileResource(filename);
  if (unique_file != -1)
    file=fdopen(unique_file,"STR");
  if ((unique_file == -1) || (file == (FILE *) NULL))
    ThrowImageException(FileOpenError,"STR");
  length=fwrite("STR",1,10,file);
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,image->columns);
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,image->rows);
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,8,file);
  strip_offset=10+(12*14)+4+8;
  length=WriteLSBLong(file,(size_t) strip_offset);
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,(size_t) image_info->orientation);
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,image->rows);
  length=fwrite("STR",1,12,file);
  offset=(ssize_t) ftell(file)-4;
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,(size_t) (strip_offset-8));
  length=fwrite("STR",1,8,file);
  length=WriteLSBLong(file,(size_t) (strip_offset-8));
  length=fwrite("STR",1,12,file);
  length=fwrite("STR",1,4,file);
  length=WriteLSBLong(file,(long) image->resolution.x);
  length=WriteLSBLong(file,1);
  for (length=0; (c=ReadBlobByte(image)) != EOF; length++)
    (void) fputc(c,file);
  offset=(ssize_t) fseek(file,(ssize_t) offset,SEEK_SET);
  length=WriteLSBLong(file,(unsigned int) length);
  (void) fclose(file);
  (void) CloseBlob(image);
  image=DestroyImage(image);
  
  read_info=CloneImageInfo((ImageInfo *) NULL);
  (void) FormatLocaleString(read_info->filename,MagickPathExtent,"STR",filename);
  image=ReadTIFFImage(read_info,exception);
  read_info=DestroyImageInfo(read_info);
  if (image != (Image *) NULL)
    {
      (void) CopyMagickString(image->filename,image_info->filename,
        MagickPathExtent);
      (void) CopyMagickString(image->magick_filename,image_info->filename,
        MagickPathExtent);
      (void) CopyMagickString(image->magick,"STR",MagickPathExtent);
    }
  (void) RelinquishUniqueFileResource(filename);
  return(image);
}