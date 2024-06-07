MagickExport void GetQuantumInfo(const ImageInfo *image_info,
  QuantumInfo *quantum_info)
{
  const char
    *option;

  assert(quantum_info != (QuantumInfo *) NULL);
  (void) memset(quantum_info,0,sizeof(*quantum_info));
  quantum_info->quantum=8;
  quantum_info->maximum=1.0;
  quantum_info->scale=QuantumRange;
  quantum_info->pack=MagickTrue;
  quantum_info->semaphore=AcquireSemaphoreInfo();
  quantum_info->signature=MagickCoreSignature;
  if (image_info == (const ImageInfo *) NULL)
    return;
  option=GetImageOption(image_info,"STR");
  if (option != (char *) NULL)
    quantum_info->format=(QuantumFormatType) ParseCommandOption(
      MagickQuantumFormatOptions,MagickFalse,option);
  option=GetImageOption(image_info,"STR");
  if (option != (char *) NULL)
    quantum_info->minimum=StringToDouble(option,(char **) NULL);
  option=GetImageOption(image_info,"STR");
  if (option != (char *) NULL)
    quantum_info->maximum=StringToDouble(option,(char **) NULL);
  if ((quantum_info->minimum == 0.0) && (quantum_info->maximum == 0.0))
    quantum_info->scale=0.0;
  else
    if (quantum_info->minimum == quantum_info->maximum)
      {
        quantum_info->scale=(double) QuantumRange/quantum_info->minimum;
        quantum_info->minimum=0.0;
      }
    else
      quantum_info->scale=(double) QuantumRange/(quantum_info->maximum-
        quantum_info->minimum);
  option=GetImageOption(image_info,"STR");
  if (option != (char *) NULL)
    quantum_info->scale=StringToDouble(option,(char **) NULL);
  option=GetImageOption(image_info,"STR");
  if (option != (char *) NULL)
    quantum_info->min_is_white=LocaleCompare(option,"STR") == 0 ?
      MagickTrue : MagickFalse;
  quantum_info->endian=image_info->endian;
  ResetQuantumState(quantum_info);
}