static MagickBooleanType GetICCProperty(const Image *image,const char *property,
  ExceptionInfo *exception)
{
  const StringInfo
    *profile;

  magick_unreferenced(property);

  profile=GetImageProfile(image,"STR");
  if (profile == (StringInfo *) NULL)
    profile=GetImageProfile(image,"STR");
  if (profile == (StringInfo *) NULL)
    return(MagickFalse);
  if (GetStringInfoLength(profile) < 128)
    return(MagickFalse);  
#if defined(MAGICKCORE_LCMS_DELEGATE)
  {
    cmsHPROFILE
      icc_profile;

    icc_profile=cmsOpenProfileFromMem(GetStringInfoDatum(profile),
      (cmsUInt32Number) GetStringInfoLength(profile));
    if (icc_profile != (cmsHPROFILE *) NULL)
      {
#if defined(LCMS_VERSION) && (LCMS_VERSION < 2000)
        const char
          *name;

        name=cmsTakeProductName(icc_profile);
        if (name != (const char *) NULL)
          (void) SetImageProperty((Image *) image,"STR",name,exception);
#else
        char
          info[MagickPathExtent];

        (void) cmsGetProfileInfoASCII(icc_profile,cmsInfoDescription,"STR",
          info,MagickPathExtent);
        (void) SetImageProperty((Image *) image,"STR",info,
          exception);
        (void) cmsGetProfileInfoASCII(icc_profile,cmsInfoManufacturer,"STR",
          info,MagickPathExtent);
        (void) SetImageProperty((Image *) image,"STR",info,
          exception);
        (void) cmsGetProfileInfoASCII(icc_profile,cmsInfoModel,"STR",info,
          MagickPathExtent);
        (void) SetImageProperty((Image *) image,"STR",info,exception);
        (void) cmsGetProfileInfoASCII(icc_profile,cmsInfoCopyright,"STR",
          info,MagickPathExtent);
        (void) SetImageProperty((Image *) image,"STR",info,exception);
#endif
        (void) cmsCloseProfile(icc_profile);
      }
  }
#endif
  return(MagickTrue);
}