static boolean ReadICCProfile(j_decompress_ptr jpeg_info)
{
  char
    magick[12];

  ErrorManager
    *error_manager;

  Image
    *image;

  MagickBooleanType
    status;

  register ssize_t
    i;

  register unsigned char
    *p;

  size_t
    length;

  StringInfo
    *icc_profile,
    *profile;

  
  length=(size_t) ((size_t) GetCharacter(jpeg_info) << 8);
  length+=(size_t) GetCharacter(jpeg_info);
  length-=2;
  if (length <= 14)
    {
      while (length-- > 0)
        if (GetCharacter(jpeg_info) == EOF)
          break;
      return(TRUE);
    }
  for (i=0; i < 12; i++)
    magick[i]=(char) GetCharacter(jpeg_info);
  if (LocaleCompare(magick,ICC_PROFILE) != 0)
    {
      
      for (i=0; i < (ssize_t) (length-12); i++)
        if (GetCharacter(jpeg_info) == EOF)
          break;
      return(TRUE);
    }
  (void) GetCharacter(jpeg_info);  
  (void) GetCharacter(jpeg_info);  
  length-=14;
  error_manager=(ErrorManager *) jpeg_info->client_data;
  image=error_manager->image;
  profile=BlobToStringInfo((const void *) NULL,length);
  if (profile == (StringInfo *) NULL)
    {
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        ResourceLimitError,"STR",image->filename);
      return(FALSE);
    }
  error_manager->profile=profile;
  p=GetStringInfoDatum(profile);
  for (i=0; i < (ssize_t) length; i++)
  {
    int
      c;

    c=GetCharacter(jpeg_info);
    if (c == EOF)
      break;
    *p++=(unsigned char) c;
  }
  if (i != (ssize_t) length)
    {
      profile=DestroyStringInfo(profile);
      (void) ThrowMagickException(&image->exception,GetMagickModule(),
        CorruptImageError,"STR",
        image->filename);
      return(FALSE);
    }
  error_manager->profile=NULL;
  icc_profile=(StringInfo *) GetImageProfile(image,"STR");
  if (icc_profile != (StringInfo *) NULL)
    {
      ConcatenateStringInfo(icc_profile,profile);
      profile=DestroyStringInfo(profile);
    }
  else
    {
      status=SetImageProfile(image,"STR",profile);
      profile=DestroyStringInfo(profile);
      if (status == MagickFalse)
        {
          (void) ThrowMagickException(&image->exception,GetMagickModule(),
            ResourceLimitError,"STR",image->filename);
          return(FALSE);
        }
    }
  if (image->debug != MagickFalse)
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
      "STR",(double) length);
  return(TRUE);
}