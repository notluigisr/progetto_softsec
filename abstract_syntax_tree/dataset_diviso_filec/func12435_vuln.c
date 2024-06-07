static Image *ReadDOTImage(const ImageInfo *image_info,ExceptionInfo *exception)
{
  char
    command[MaxTextExtent];

  const char
    *option;

  graph_t
    *graph;

  Image
    *image;

  ImageInfo
    *read_info;

  MagickBooleanType
    status;

  
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickCoreSignature);
  if (image_info->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",
      image_info->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  assert(graphic_context != (GVC_t *) NULL);
  image=AcquireImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFalse)
    {
      image=DestroyImageList(image);
      return((Image *) NULL);
    }
  read_info=CloneImageInfo(image_info);
  SetImageInfoBlob(read_info,(void *) NULL,0);
  (void) CopyMagickString(read_info->magick,"STR",MaxTextExtent);
  (void) AcquireUniqueFilename(read_info->filename);
  (void) FormatLocaleString(command,MaxTextExtent,"STR",
    read_info->filename,image_info->filename);
#if !defined(WITH_CGRAPH)
  graph=agread(GetBlobFileHandle(image));
#else
  graph=agread(GetBlobFileHandle(image),(Agdisc_t *) NULL);
#endif
  if (graph == (graph_t *) NULL)
    {
      (void) RelinquishUniqueFileResource(read_info->filename);
      return ((Image *) NULL);
    }
  option=GetImageOption(image_info,"STR");
  if (option == (const char *) NULL)
    gvLayout(graphic_context,graph,(char *) "STR");
  else
    gvLayout(graphic_context,graph,(char *) option);
  gvRenderFilename(graphic_context,graph,(char *) "STR",read_info->filename);
  gvFreeLayout(graphic_context,graph);
  agclose(graph);
  
  (void) CopyMagickString(read_info->magick,"STR",MaxTextExtent);
  image=ReadImage(read_info,exception);
  (void) RelinquishUniqueFileResource(read_info->filename);
  read_info=DestroyImageInfo(read_info);
  if (image == (Image *) NULL)
    return((Image *) NULL);
  return(GetFirstImageInList(image));
}