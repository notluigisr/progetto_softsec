WandExport double DrawGetStrokeDashOffset(const DrawingWand *wand)
{
  assert(wand != (const DrawingWand *) NULL);
  assert(wand->signature == MagickWandSignature);
  if (wand->debug != MagickFalse)
    (void) LogMagickEvent(WandEvent,GetMagickModule(),"STR",wand->name);
  return(CurrentContext->dash_offset);
}