MagickPrivate void XDestroyWindowColors(Display *display,Window window)
{
  Atom
    property,
    type;

  int
    format;

  Status
    status;

  unsigned char
    *data;

  unsigned long
    after,
    length;

  
  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR");
  assert(display != (Display *) NULL);
  property=XInternAtom(display,"STR",MagickFalse);
  if (property == (Atom) NULL)
    {
      ThrowXWindowException(XServerError,"STR",
        "STR");
      return;
    }
  status=XGetWindowProperty(display,window,property,0L,1L,MagickTrue,
    (Atom) AnyPropertyType,&type,&format,&length,&after,&data);
  if (status != Success)
    return;
  if ((type == XA_PIXMAP) && (format == 32) && (length == 1) && (after == 0))
    {
      (void) XKillClient(display,(XID) (*((Pixmap *) data)));
      (void) XDeleteProperty(display,window,property);
    }
  if (type != None)
    (void) XFree((void *) data);
}