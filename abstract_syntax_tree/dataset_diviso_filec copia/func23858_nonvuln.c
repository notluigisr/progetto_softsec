WandExport void DrawPathLineToHorizontalAbsolute(DrawingWand *wand,
  const double x)
{
  assert(wand != (DrawingWand *) NULL);
  assert(wand->signature == MagickWandSignature);
  if (wand->debug != MagickFalse)
    (void) LogMagickEvent(WandEvent,GetMagickModule(),"STR",wand->name);
  DrawPathLineToHorizontal(wand,AbsolutePathMode,x);
}