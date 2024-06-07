static void TIFFGetEXIFProperties(TIFF *tiff,Image *image,
  ExceptionInfo *exception)
{
#if defined(MAGICKCORE_HAVE_TIFFREADEXIFDIRECTORY)
  char
    value[MagickPathExtent];

  register ssize_t
    i;

  tdir_t
    directory;

#if defined(TIFF_VERSION_BIG)
  uint64
#else
  uint32
#endif
    offset;

  void
    *sans[2] = { NULL, NULL };

  
  offset=0;
  if (TIFFGetField(tiff,TIFFTAG_EXIFIFD,&offset) != 1)
    return;
  directory=TIFFCurrentDirectory(tiff);
  if (TIFFReadEXIFDirectory(tiff,offset) != 1)
    {
      TIFFSetDirectory(tiff,directory);
      return;
    }
  for (i=0; exif_info[i].tag != 0; i++)
  {
    *value='\0';
    switch (exif_info[i].type)
    {
      case TIFF_ASCII:
      {
        char
          *ascii;

        ascii=(char *) NULL;
        if ((TIFFGetField(tiff,exif_info[i].tag,&ascii,sans) == 1) &&
            (ascii != (char *) NULL) && (*ascii != '\0'))
          (void) CopyMagickString(value,ascii,MagickPathExtent);
        break;
      }
      case TIFF_SHORT:
      {
        if (exif_info[i].variable_length == 0)
          {
            uint16
              shorty;

            shorty=0;
            if (TIFFGetField(tiff,exif_info[i].tag,&shorty,sans) == 1)
              (void) FormatLocaleString(value,MagickPathExtent,"STR",shorty);
          }
        else if (exif_info[i].variable_length == 2)
        {
          uint16
            *shorty;
 
          shorty=0;
          if ((TIFFGetField(tiff,exif_info[i].tag,&shorty,sans) == 1) &&
              (shorty != (uint16 *) NULL))
            (void) FormatLocaleString(value,MagickPathExtent,"STR",*shorty);
        }
        else
          {
            int
              tiff_status;

            uint16
              *shorty;

            uint16
              shorty_num;

            tiff_status=TIFFGetField(tiff,exif_info[i].tag,&shorty_num,&shorty,
              sans);
            if (tiff_status == 1)
              (void) FormatLocaleString(value,MagickPathExtent,"STR",
                shorty_num != 0 ? shorty[0] : 0);
          }
        break;
      }
      case TIFF_LONG:
      {
        uint32
          longy;

        longy=0;
        if (TIFFGetField(tiff,exif_info[i].tag,&longy,sans) == 1)
          (void) FormatLocaleString(value,MagickPathExtent,"STR",longy);
        break;
      }
#if defined(TIFF_VERSION_BIG)
      case TIFF_LONG8:
      {
        uint64
          long8y;

        long8y=0;
        if (TIFFGetField(tiff,exif_info[i].tag,&long8y,sans) == 1)
          (void) FormatLocaleString(value,MagickPathExtent,"STR",(double)
            ((MagickOffsetType) long8y));
        break;
      }
#endif
      case TIFF_RATIONAL:
      case TIFF_SRATIONAL:
      case TIFF_FLOAT:
      {
        float
          floaty;

        floaty=0.0;
        if (TIFFGetField(tiff,exif_info[i].tag,&floaty,sans) == 1)
          (void) FormatLocaleString(value,MagickPathExtent,"STR",(double)
            floaty);
        break;
      }
      case TIFF_DOUBLE:
      {
        double
          doubley;

        doubley=0.0;
        if (TIFFGetField(tiff,exif_info[i].tag,&doubley,sans) == 1)
          (void) FormatLocaleString(value,MagickPathExtent,"STR",doubley);
        break;
      }
      default:
        break;
    }
    if (*value != '\0')
      (void) SetImageProperty(image,exif_info[i].property,value,exception);
  }
  TIFFSetDirectory(tiff,directory);
#else
  (void) tiff;
  (void) image;
#endif
}