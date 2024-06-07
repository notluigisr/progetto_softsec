WandExport MagickBooleanType PushDrawingWand(DrawingWand *wand)
{
  assert(wand != (DrawingWand *) NULL);
  assert(wand->signature == MagickWandSignature);
  if (wand->debug != MagickFalse)
    (void) LogMagickEvent(WandEvent,GetMagickModule(),"STR",wand->name);
  wand->index++;
  wand->graphic_context=(DrawInfo **) ResizeQuantumMemory(wand->graphic_context,
    (size_t) wand->index+1UL,sizeof(*wand->graphic_context));
  if (wand->graphic_context == (DrawInfo **) NULL)
    {
      wand->index--;
      ThrowDrawException(ResourceLimitError,"STR",
        wand->name);
      return(MagickFalse);
    }
  CurrentContext=CloneDrawInfo((ImageInfo *) NULL,
    wand->graphic_context[wand->index-1]);
  (void) MVGPrintf(wand,"STR");
  wand->indent_depth++;
  return(MagickTrue);
}