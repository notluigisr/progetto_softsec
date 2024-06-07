MagickExport Image *WaveImage(const Image *image,const double amplitude,
  const double wave_length,const PixelInterpolateMethod method,
  ExceptionInfo *exception)
{


  CacheView
    *image_view,
    *wave_view;

  Image
    *wave_image;

  MagickBooleanType
    status;

  MagickOffsetType
    progress;

  double
    *sine_map;

  register ssize_t
    i;

  ssize_t
    y;

  
  assert(image != (Image *) NULL);
  assert(image->signature == MagickCoreSignature);
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR",image->filename);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickCoreSignature);
  wave_image=CloneImage(image,image->columns,(size_t) (image->rows+2.0*
    fabs(amplitude)),MagickTrue,exception);
  if (wave_image == (Image *) NULL)
    return((Image *) NULL);
  if (SetImageStorageClass(wave_image,DirectClass,exception) == MagickFalse)
    {
      wave_image=DestroyImage(wave_image);
      return((Image *) NULL);
    }
  if (wave_image->background_color.alpha != OpaqueAlpha)
    wave_image->alpha_trait=BlendPixelTrait;
  
  sine_map=(double *) AcquireQuantumMemory((size_t) wave_image->columns,
    sizeof(*sine_map));
  if (sine_map == (double *) NULL)
    {
      wave_image=DestroyImage(wave_image);
      ThrowImageException(ResourceLimitError,"STR");
    }
  for (i=0; i < (ssize_t) wave_image->columns; i++)
    sine_map[i]=fabs(amplitude)+amplitude*sin((double) ((2.0*MagickPI*i)/
      wave_length));
  
  status=MagickTrue;
  progress=0;
  image_view=AcquireVirtualCacheView(image,exception);
  wave_view=AcquireAuthenticCacheView(wave_image,exception);
  (void) SetCacheViewVirtualPixelMethod(image_view,
    BackgroundVirtualPixelMethod);
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  #pragma omp parallel for schedule(static,4) shared(progress,status) \
    magick_threads(image,wave_image,wave_image->rows,1)
#endif
  for (y=0; y < (ssize_t) wave_image->rows; y++)
  {
    register Quantum
      *magick_restrict q;

    register ssize_t
      x;

    if (status == MagickFalse)
      continue;
    q=QueueCacheViewAuthenticPixels(wave_view,0,y,wave_image->columns,1,
      exception);
    if (q == (Quantum *) NULL)
      {
        status=MagickFalse;
        continue;
      }
    for (x=0; x < (ssize_t) wave_image->columns; x++)
    {
      status=InterpolatePixelChannels(image,image_view,wave_image,method,
        (double) x,(double) (y-sine_map[x]),q,exception);
      q+=GetPixelChannels(wave_image);
    }
    if (SyncCacheViewAuthenticPixels(wave_view,exception) == MagickFalse)
      status=MagickFalse;
    if (image->progress_monitor != (MagickProgressMonitor) NULL)
      {
        MagickBooleanType
          proceed;

#if defined(MAGICKCORE_OPENMP_SUPPORT)
        #pragma omp critical (MagickCore_WaveImage)
#endif
        proceed=SetImageProgress(image,WaveImageTag,progress++,image->rows);
        if (proceed == MagickFalse)
          status=MagickFalse;
      }
  }
  wave_view=DestroyCacheView(wave_view);
  image_view=DestroyCacheView(image_view);
  sine_map=(double *) RelinquishMagickMemory(sine_map);
  if (status == MagickFalse)
    wave_image=DestroyImage(wave_image);
  return(wave_image);
}