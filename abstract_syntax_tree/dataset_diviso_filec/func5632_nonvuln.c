MagickExport Image *FlopImage(const Image *image,ExceptionInfo *exception)
{


  CacheView
    *flop_view,
    *image_view;

  Image
    *flop_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  RectangleInfo
    page;

  ssize_t
    y;

  assert(image != (const Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  flop_image=CloneImage(image,image->columns,image->rows,MagickTrue,exception);
  if (flop_image == (Image *) NULL)
    return((Image *) NULL);
  
  status=MagickTrue;
  progress=0;
  page=image->page;
  image_view=AcquireVirtualCacheView(image,exception);
  flop_view=AcquireAuthenticCacheView(flop_image,exception);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static,4) shared(status) \
    magick_threads(image,flop_image,1,1)
#endif
  for (y=0; y < (ssize_t) flop_image->rows; y++)
  {
    register const Quantum
      *restrict p;

    register ssize_t
      x;

    register Quantum
      *restrict q;

    if (status == MagickFalse)
      continue;
    p=GetCacheViewVirtualPixels(image_view,0,y,image->columns,1,exception);
    q=QueueCacheViewAuthenticPixels(flop_view,0,y,flop_image->columns,1,
      exception);
    if ((p == (const Quantum *) NULL) || (q == (Quantum *) NULL))
      {
        status=MagickFalse;
        continue;
      }
    q+=GetPixelChannels(flop_image)*flop_image->columns;
    for (x=0; x < (ssize_t) flop_image->columns; x++)
    {
      register ssize_t
        i;

      q-=GetPixelChannels(flop_image);
      if (GetPixelReadMask(image,p) == 0)
        {
          p+=GetPixelChannels(image);
          continue;
        }
      for (i=0; i < (ssize_t) GetPixelChannels(image); i++)
      {
        PixelChannel channel=GetPixelChannelChannel(image,i);
        PixelTrait traits=GetPixelChannelTraits(image,channel);
        PixelTrait flop_traits=GetPixelChannelTraits(flop_image,channel);
        if ((traits == UndefinedPixelTrait) ||
            (flop_traits == UndefinedPixelTrait))
          continue;
        SetPixelChannel(flop_image,channel,p[i],q);
      }
      p+=GetPixelChannels(image);
    }
    if (SyncCacheViewAuthenticPixels(flop_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp critical (MagickCore_FlopImage)
#endif
        proceed=SetImageProgress(image,FlopImageTag,progress++,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  flop_view=DestroyCacheView(flop_view);
  image_view=DestroyCacheView(image_view);
  flop_image->type=image->type;
  if (page.width != 0)
    page.x=(ssize_t) (page.width-flop_image->columns-page.x);
  flop_image->page=page;
  if (status == MagickFalse)
    flop_image=DestroyImage(flop_image);
  return(flop_image);
}