static MagickBooleanType ReadHEICImageByID(const ImageInfo *image_info,
  Image *image,struct heif_context *heif_context,heif_item_id image_id,
  ExceptionInfo *exception)
{
  const char
    *option;

  int
    stride_y,
    stride_cb,
    stride_cr;

  MagickBooleanType
    status;

  ssize_t
    y;

  struct heif_decoding_options
    *decode_options;

  struct heif_error
    error;

  struct heif_image
    *heif_image;

  struct heif_image_handle
    *image_handle;

  const uint8_t
    *p_y,
    *p_cb,
    *p_cr;

  error=heif_context_get_image_handle(heif_context,image_id,&image_handle);
  if (IsHeifSuccess(&error,image,exception) == MagickFalse)
    return(MagickFalse);
  if (ReadHEICColorProfile(image,image_handle,exception) == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      return(MagickFalse);
    }
  if (ReadHEICExifProfile(image,image_handle,exception) == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      return(MagickFalse);
    }
  
  image->depth=8;
  image->columns=(size_t) heif_image_handle_get_width(image_handle);
  image->rows=(size_t) heif_image_handle_get_height(image_handle);
  if (image_info->ping != MagickFalse)
    {
      image->colorspace=YCbCrColorspace;
      heif_image_handle_release(image_handle);
      return(MagickTrue);
    }
  if (HEICSkipImage(image_info,image) != MagickFalse)
    {
      heif_image_handle_release(image_handle);
      return(MagickTrue);
    }
  status=SetImageExtent(image,image->columns,image->rows,exception);
  if (status == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      return(MagickFalse);
    }
  
  (void) SetImageColorspace(image,YCbCrColorspace,exception);
  decode_options=(struct heif_decoding_options *) NULL;
  option=GetImageOption(image_info,"STR");
  if (IsStringTrue(option) == MagickTrue)
    {
      decode_options=heif_decoding_options_alloc();
      decode_options->ignore_transformations=1;
    }
  else
    (void) SetImageProperty(image,"STR",exception);
  error=heif_decode_image(image_handle,&heif_image,heif_colorspace_YCbCr,
    heif_chroma_420,decode_options);
  if (IsHeifSuccess(&error,image,exception) == MagickFalse)
    {
      heif_image_handle_release(image_handle);
      return(MagickFalse);
    }
  if (decode_options != (struct heif_decoding_options *) NULL)
    {
      
      image->columns=(size_t) heif_image_get_width(heif_image,heif_channel_Y);
      image->rows=(size_t) heif_image_get_height(heif_image,heif_channel_Y);
      status=SetImageExtent(image,image->columns,image->rows,exception);
      heif_decoding_options_free(decode_options);
      if (status == MagickFalse)
        {
          heif_image_release(heif_image);
          heif_image_handle_release(image_handle);
          return(MagickFalse);
        }
    }
  p_y=heif_image_get_plane_readonly(heif_image,heif_channel_Y,&stride_y);
  p_cb=heif_image_get_plane_readonly(heif_image,heif_channel_Cb,&stride_cb);
  p_cr=heif_image_get_plane_readonly(heif_image,heif_channel_Cr,&stride_cr);
  for (y=0; y < (ssize_t) image->rows; y++)
  {
    Quantum
      *q;

    register ssize_t
      x;

    q=QueueAuthenticPixels(image,0,y,image->columns,1,exception);
    if (q == (Quantum *) NULL)
      break;
    for (x=0; x < (ssize_t) image->columns; x++)
    {
      SetPixelRed(image,ScaleCharToQuantum((unsigned char) p_y[y*
        stride_y+x]),q);
      SetPixelGreen(image,ScaleCharToQuantum((unsigned char) p_cb[(y/2)*
        stride_cb+x/2]),q);
      SetPixelBlue(image,ScaleCharToQuantum((unsigned char) p_cr[(y/2)*
        stride_cr+x/2]),q);
      q+=GetPixelChannels(image);
    }
    if (SyncAuthenticPixels(image,exception) == MagickFalse)
      break;
  }
  heif_image_release(heif_image);
  heif_image_handle_release(image_handle);
  return(MagickTrue);
}