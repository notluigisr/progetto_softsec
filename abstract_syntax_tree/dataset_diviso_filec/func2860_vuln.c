static void TIFFGetProperties(TIFF *tiff,Image *image,ExceptionInfo *exception)
{
  char
    message[MagickPathExtent],
    *text;

  uint32
    count,
    length,
    type;

  unsigned long
    *tietz;


  if (TIFFGetField(tiff,TIFFTAG_ARTIST,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_COPYRIGHT,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_DATETIME,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_DOCUMENTNAME,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_HOSTCOMPUTER,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_IMAGEDESCRIPTION,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_MAKE,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_MODEL,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_OPIIMAGEID,&count,&text) == 1)
    {
      if (count >= MagickPathExtent)
        count=MagickPathExtent-1;
      (void) CopyMagickString(message,text,count+1);
      (void) SetImageProperty(image,"STR",message,exception);
    }
  if (TIFFGetField(tiff,TIFFTAG_PAGENAME,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,TIFFTAG_SOFTWARE,&text) == 1)
    (void) SetImageProperty(image,"STR",text,exception);
  if (TIFFGetField(tiff,33423,&count,&text) == 1)
    {
      if (count >= MagickPathExtent)
        count=MagickPathExtent-1;
      (void) CopyMagickString(message,text,count+1);
      (void) SetImageProperty(image,"STR",message,exception);
    }
  if (TIFFGetField(tiff,36867,&count,&text) == 1)
    {
      if (count >= MagickPathExtent)
        count=MagickPathExtent-1;
      (void) CopyMagickString(message,text,count+1);
      (void) SetImageProperty(image,"STR",message,exception);
    }
  if (TIFFGetField(tiff,TIFFTAG_SUBFILETYPE,&type) == 1)
    switch (type)
    {
      case 0x01:
      {
        (void) SetImageProperty(image,"STR",
          exception);
        break;
      }
      case 0x02:
      {
        (void) SetImageProperty(image,"STR",exception);
        break;
      }
      case 0x04:
      {
        (void) SetImageProperty(image,"STR",exception);
        break;
      }
      default:
        break;
    }
  if (TIFFGetField(tiff,37706,&length,&tietz) == 1)
    {
      (void) FormatLocaleString(message,MagickPathExtent,"STR",tietz[0]);
      (void) SetImageProperty(image,"STR",message,exception);
    }
}