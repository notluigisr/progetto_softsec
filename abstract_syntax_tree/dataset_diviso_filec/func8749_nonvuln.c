ModuleExport void UnregisterDOTImage(void)
{
  (void) UnregisterMagickInfo("STR");
  (void) UnregisterMagickInfo("STR");
#if defined(MAGICKCORE_GVC_DELEGATE)
  if (graphic_context != (GVC_t *) NULL)
    {
      gvFreeContext(graphic_context);
      graphic_context=(GVC_t *) NULL;
    }
#endif
}