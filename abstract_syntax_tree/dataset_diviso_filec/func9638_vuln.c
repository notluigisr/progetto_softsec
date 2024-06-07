static MagickBooleanType TIFFGetProfiles(TIFF *tiff,Image *image,
  ExceptionInfo *exception)
{
  MagickBooleanType
    status;

  uint32
    length = 0;

  unsigned char
    *profile = (unsigned char *) NULL;

  status=MagickTrue;
#if defined(TIFFTAG_ICCPROFILE)
  if ((TIFFGetField(tiff,TIFFTAG_ICCPROFILE,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    status=ReadProfile(image,"STR",profile,(ssize_t) length,exception);
#endif
#if defined(TIFFTAG_PHOTOSHOP)
  if ((TIFFGetField(tiff,TIFFTAG_PHOTOSHOP,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    status=ReadProfile(image,"STR",profile,(ssize_t) length,exception);
#endif
#if defined(TIFFTAG_RICHTIFFIPTC)
  if ((TIFFGetField(tiff,TIFFTAG_RICHTIFFIPTC,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    {
      if (TIFFIsByteSwapped(tiff) != 0)
        TIFFSwabArrayOfLong((uint32 *) profile,(size_t) length);
      status=ReadProfile(image,"STR",profile,4L*length,exception);
    }
#endif
#if defined(TIFFTAG_XMLPACKET)
  if ((TIFFGetField(tiff,TIFFTAG_XMLPACKET,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    {
      StringInfo
        *dng;

      status=ReadProfile(image,"STR",profile,(ssize_t) length,exception);
      dng=BlobToStringInfo(profile,length);
      if (dng != (StringInfo *) NULL)
        {
          const char
            *target = "STR";

          if (strstr((char *) GetStringInfoDatum(dng),target) != (char *) NULL)
            (void) CopyMagickString(image->magick,"STR",MagickPathExtent);
          dng=DestroyStringInfo(dng);
        }
    }
#endif
  if ((TIFFGetField(tiff,34118,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    status=ReadProfile(image,"STR",profile,(ssize_t) length,
      exception);
  if ((TIFFGetField(tiff,37724,&length,&profile) == 1) &&
      (profile != (unsigned char *) NULL))
    status=ReadProfile(image,"STR",profile,(ssize_t) length,exception);
  return(status);
}