MagickExport MagickBooleanType RemapImages(const QuantizeInfo *quantize_info,
  Image *images,const Image *remap_image)
{
  CubeInfo
    *cube_info;

  Image
    *image;

  MagickBooleanType
    status;

  assert(images != (Image *) NULL);
  assert(images->signature == MagickCoreSignature);
  if (images->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",images->filename);
  image=images;
  if (remap_image == (Image *) NULL)
    {
      
      status=QuantizeImages(quantize_info,images);
      return(status);
    }
  
  cube_info=GetCubeInfo(quantize_info,MaxTreeDepth,
    quantize_info->number_colors);
  if (cube_info == (CubeInfo *) NULL)
    ThrowBinaryImageException(ResourceLimitError,"STR",
      image->filename);
  status=ClassifyImageColors(cube_info,remap_image,&image->exception);
  if (status != MagickFalse)
    {
      
      cube_info->quantize_info->number_colors=cube_info->colors;
      image=images;
      for ( ; image != (Image *) NULL; image=GetNextImageInList(image))
      {
        status=AssignImageColors(image,cube_info);
        if (status == MagickFalse)
          break;
      }
    }
  DestroyCubeInfo(cube_info);
  return(status);
}