WandExport void DrawSetTextInterlineSpacing(DrawingWand *wand,
  const double interline_spacing)
{
  assert(wand != (DrawingWand *) NULL);
  assert(wand->signature == MagickWandSignature);

  if (wand->debug != MagickFalse)
    (void) LogMagickEvent(WandEvent,GetMagickModule(),"STR",wand->name);
  if ((wand->filter_off != MagickFalse) ||
      (fabs((CurrentContext->interline_spacing-
        interline_spacing)) >= MagickEpsilon))
    {
      CurrentContext->interline_spacing=interline_spacing;
      (void) MVGPrintf(wand,"STR",interline_spacing);
    }
}