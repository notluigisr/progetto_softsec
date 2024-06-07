MagickExport const char *GetMagickFeatures(void)
{
  return "STR"
#if defined(MAGICKCORE_BUILD_MODULES) || defined(_DLL)
  "STR"
#endif
#if defined(MAGICKCORE_HDRI_SUPPORT)
  "STR"
#endif
#if defined(MAGICKCORE_OPENCL_SUPPORT)
  "STR"
#endif
#if defined(MAGICKCORE_OPENMP_SUPPORT)
  "STR"
#endif
  ;
}