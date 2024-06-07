static MagickBooleanType MonitorProgress(const char *text,
  const MagickOffsetType offset,const MagickSizeType extent,
  void *wand_unused(client_data))
{
  char
    message[MagickPathExtent],
    tag[MagickPathExtent];

  const char
    *locale_message;

  register char
    *p;

  magick_unreferenced(client_data);

  if ((extent <= 1) || (offset < 0) || (offset >= (MagickOffsetType) extent))
    return(MagickTrue);
  if ((offset != (MagickOffsetType) (extent-1)) && ((offset % 50) != 0))
    return(MagickTrue);
  (void) CopyMagickString(tag,text,MagickPathExtent);
  p=strrchr(tag,'/');
  if (p != (char *) NULL)
    *p='\0';
  (void) FormatLocaleString(message,MagickPathExtent,"STR",tag);
  locale_message=GetLocaleMessage(message);
  if (locale_message == message)
    locale_message=tag;
  if (p == (char *) NULL)
    (void) FormatLocaleFile(stderr,"STR",
      locale_message,(long) offset,(unsigned long) extent,(long)
      (100L*offset/(extent-1)));
  else
    (void) FormatLocaleFile(stderr,"STR",
      locale_message,p+1,(long) offset,(unsigned long) extent,(long)
      (100L*offset/(extent-1)));
  if (offset == (MagickOffsetType) (extent-1))
    (void) FormatLocaleFile(stderr,"STR");
  (void) fflush(stderr);
  return(MagickTrue);
}